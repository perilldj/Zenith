#include "../header/Conv2D.h"
#include <iomanip>

Conv2DLayer::Conv2DLayer() { }

/*
    void Conv2DLayer::InitializeLayer()
    Description: Initializes the convolutional layer, creating properly sized matrices with
                 respect to the input shape and output count.
*/

void Conv2DLayer::InitializeLayer() {

    outputChannels = kernelCount;
    outputWidth = inputWidth - ((kernelSize % 2) + 1);
    outputHeight = inputHeight - ((kernelSize % 2) + 1);

    if(isInputLayer)
        dataIn = std::make_shared<Matrix>(inputChannels, inputWidth, inputHeight);

    zOutputs = std::make_shared<Matrix>(outputChannels, outputWidth, outputHeight);
    aOutputs = std::make_shared<Matrix>(outputChannels, outputWidth, outputHeight);
    dCdz = std::make_shared<Matrix>(*zOutputs.get());
    g_Activations = std::make_shared<Matrix>(outputChannels, outputWidth, outputHeight);

    kernels.resize(kernelCount);
    g_kernels.resize(kernelCount);
    rotatedKernels.resize(kernelCount);

    for(int i = 0; i < kernelCount; i++) {
        kernels[i] = std::make_shared<Matrix>(inputChannels, kernelSize, kernelSize);
        g_kernels[i] = std::make_shared<Matrix>(inputChannels, kernelSize, kernelSize);
        rotatedKernels[i] = std::make_shared<Matrix>(inputChannels, kernelSize, kernelSize);
    }
    
    biases = std::make_shared<Matrix>(1, kernelCount, 1);
    g_biases = std::make_shared<Matrix>(1, kernelCount, 1);

}

/*
    int Conv2DLayer::GetParameterCount()
    Description: Returns the total number of parameters in this layer.
*/


int Conv2DLayer::GetParameterCount() {
    return kernelCount * kernelSize * kernelSize + kernelCount;
}

/*
    void Conv2DLayer::PrintLayerInformation()
    Description: Prints the name of the layer, the activation function, and
                 the number of parameters to the screen, properly spaced with
                 respect to Network::PrintNetworkStructure() function.
*/

void Conv2DLayer::PrintLayerInformation() {
    std::stringstream ss;
    ss << "(" << outputChannels << ", " << outputHeight << ", " << outputWidth << ")";
    std::cout << std::left << std::setw(19) << "Conv2D" 
                           << std::setw(18) << ss.str()
                           << std::setw(18) << activation 
                           << std::setw(18) << GetParameterCount() << std::endl;
}

/*
    void Conv2DLayer::Evaluate()
    Description: Evaluates the current layer based on the output of the previous layer.
                 If this layer is the first in the network, the data is fetched
                 from the dataIn matrix.
*/

void Conv2DLayer::Evaluate() {

    if(isInputLayer)
        Matrix::Convolution(Matrix::STANDARD_CONVOLUTION, *dataIn.get(), *kernels.get(), *zOutputs.get(), true);
    else
        Matrix::Convolution(Matrix::STANDARD_CONVOLUTION, *(previousLayer->aOutputs).get(), *kernels.get(), *zOutputs.get(), true);

    AddBiases();
    NMath::Activation(activation, *zOutputs.get(), *aOutputs.get());

    if(nextLayer)
        nextLayer->Evaluate();
        
}

/*
    void Conv2DLayer::Backpropagation(Matrix &gradients)
    Description: Calculates the gradients based on the provided change of cost
                 with respect to the activation output.
*/

void Conv2DLayer::Backpropagation(Matrix &gradients) {

    dCdz->Clear();
    NMath::dCdz(networkCost, activation, isOutputLayer, gradients, 
                *aOutputs.get(), *zOutputs.get(), *dCdz.get());
    CalculateBiasGradients();
    RotateKernels();

    if(isInputLayer) {
        Matrix::Convolution(Matrix::STANDARD_CONVOLUTION, *dataIn.get(), *dCdz.get(), *g_kernels.get(), false);
        Matrix::Convolution(Matrix::FULL_CONVOLUTION, *rotatedKernels.get(), *dCdz.get(), *g_Activations.get(), false);
    } else {
        Matrix::Convolution(Matrix::STANDARD_CONVOLUTION, *(previousLayer->aOutputs).get(), *dCdz.get(), *g_kernels.get(), false);
        Matrix::Convolution(Matrix::FULL_CONVOLUTION, *rotatedKernels.get(), *(previousLayer->aOutputs).get(), *g_Activations.get(), false);
    }

    if(previousLayer)
        previousLayer->Backpropagation(*g_Activations.get());

}

/*
    void Conv2DLayer::ApplyGradients(float learningRate, int batchSize)
    Description: Applies the calcualted parameter gradients accumulated from the current
                 minibatch to the actual parameters. Gradients are averaged by the batchSize
                 and scaled by the learningRate before being applied.
*/

void Conv2DLayer::ApplyGradients(float learningRate, int batchSize) {

    for(int i = 0; i < kernelCount; i++) {
        g_kernels[i]->Scale((1.0f / batchSize));
        g_kernels[i]->Scale(learningRate);
        Matrix::Subtract(*kernels[i].get(), *g_kernels[i].get(), *kernels[i].get());
        g_kernels[i]->Clear();
    }

    g_biases->Scale((1.0f / batchSize));
    g_biases->Scale(learningRate);
    Matrix::Subtract(*biases.get(), *g_biases.get(), *biases.get());
    g_biases->Clear();

}

void Conv2DLayer::CalculateBiasGradients() {

    for(int i = 0; i < kernelCount; i++) {
        float g_bias = 0.0f;
        for(int j = 0; j < inputChannels; j++)
            g_bias += AccumulateChannel(*dCdz, i * inputChannels + j);
        g_biases->Set(i, g_biases->Get(i) + g_bias);
    }

}

float Conv2DLayer::AccumulateChannel(Matrix &mat, int channel) {

    float result = 0.0f;
    
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
            result += mat.Get(channel, i, j);

    return result;

}

void Conv2DLayer::RotateKernels() {

    /*
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int index = i * width + j;
                int rotatedIndex = (height - 1 - i) * width + (width - 1 - j);
                rotated[rotatedIndex] = kernel[index];
            }
        }
    */

    for(int kernel = 0; kernel < kernelCount; kernel++) {

        for(int i = 0; i < kernelSize; i++) {
            for(int j = 0; j < kernelSize; j++) {
                int rotatedI = (kernelSize - 1 - i);
                int rotatedJ = (kernelSize - 1 - j);
                rotatedKernels->Set(kernel, rotatedI, rotatedJ, kernels->Get(kernel, i, j));
            }
        }

    }

}

void Conv2DLayer::AddBiases() {

    for(int i = 0; i < kernelCount; i++)
        AddBiasToChannel(*zOutputs.get(), i, biases->Get(i));

}

void Conv2DLayer::AddBiasToChannel(Matrix &mat, int channel, float bias) {

    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
            mat.Set(channel, i, j, mat.Get(channel, i, j) + bias);

}