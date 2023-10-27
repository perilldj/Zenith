#include "../header/Dense.h"
#include <iomanip>

DenseLayer::DenseLayer() {

}

/*
    void DenseLayer::InitializeLayer()
    Description: Initializes the dense layer, creating properly sized matrices with
                 respect to the input shape and output count.
*/

void DenseLayer::InitializeLayer() {

    outputWidth = 1;
    outputHeight = outputCount;
    outputChannels = 1;

    weights = std::make_shared<Matrix>(outputCount, inputHeight);
    g_weights = std::make_shared<Matrix>(outputCount, inputHeight);
    biases = std::make_shared<Matrix>(outputCount, 1);
    g_biases = std::make_shared<Matrix>(outputCount, 1);

    zOutputs = std::make_shared<Matrix>(outputCount, 1);
    aOutputs = std::make_shared<Matrix>(outputCount, 1);
    aOutputsTranspose = Matrix::C_Transpose(*aOutputs.get());

    if(isInputLayer)
        dataIn = std::make_shared<Matrix>(inputWidth, 1);
    else
        g_Activations = std::make_shared<Matrix>(inputHeight, inputWidth);

    NMath::InitializeWeights(initializer, distribution, *weights.get());

}

/*
    int DenseLayer::GetParameterCount()
    Description: Returns the total number of parameters in this layer.
*/

int DenseLayer::GetParameterCount() {
    int count = 0;
    count += weights->GetCol() *  weights->GetRow();
    count += biases->GetCol() * weights->GetRow();
    return count;
}

/*
    void DenseLayer::PrintLayerInformation()
    Description: Prints the name of the layer, the activation function, and
                 the number of parameters to the screen, properly spaced with
                 respect to Network::PrintNetworkStructure() function.
*/

void DenseLayer::PrintLayerInformation() {
    std::cout << std::left << std::setw(19) << "Dense" << std::setw(18) << activation 
                           << std::setw(18) << GetParameterCount() << std::endl;
}

/*
    void DenseLayer::Evaluate()
    Description: Evaluates the current layer based on the output of the previous layer.
                 If this layer is the first in the network, the data is fetched
                 from the dataIn matrix.
*/

void DenseLayer::Evaluate() {
    if(isInputLayer)    // Multiplying the input data matrix by the weight matrix
        Matrix::Product(*weights.get(), *dataIn.get(), *zOutputs.get());
    else
        Matrix::Product(*weights.get(), *(previousLayer->aOutputs.get()), *zOutputs.get());
    Matrix::Add(*zOutputs.get(), *biases.get(), *zOutputs.get());    // Add bias terms
    NMath::Activation(activation, *zOutputs.get(), *aOutputs.get()); // Apply activation function
    if(nextLayer)
        nextLayer->Evaluate(); // Continue evaluation to the next layer
}

/*
    void DenseLayer::Backpropogation(Matrix &gradients)
    Description: Calculates the gradients based on the provided change of cost
                 with respect to the activation output.
*/

void DenseLayer::Backpropogation(Matrix &gradients) {
    
    if(isInputLayer)
        return;

    /* Calculate the change of cost with respect to the pre-activation output. */
    Matrix dCdz = Matrix(gradients.GetCol(), gradients.GetRow());
    NMath::dCdz(networkCost, activation, isOutputLayer, 
                gradients, *aOutputs.get(), *zOutputs.get(), dCdz);

    /* Weight gradients are calculated by multiplying the dCdz matrix by the transpose of
       the activation outputs of the network. */
    Matrix::Transpose(*aOutputs.get(), *aOutputsTranspose.get());
    Matrix::AccumulateProduct(dCdz, *aOutputsTranspose.get(), *g_weights.get());

    /* Bias gradients are equivalend to the dCdz gradients. */
    Matrix::Add(*g_biases.get(), dCdz, *g_biases.get());

    /* Multiplying the transpose of the weight matrix by the dCdz matrix results
       in the activation gradients for the previous layer to continue backpropogation. */
    Matrix::Product(*weightsTranspose.get(), dCdz, *g_Activations.get());

    /* Continue backpropogation to the previous layer. */
    if(!previousLayer)
        previousLayer->Backpropogation(*g_Activations.get());

}

void DenseLayer::ApplyGradients(float learningRate, int batchSize) {
    g_weights->Scale(learningRate * (1.0f / batchSize));
    g_biases->Scale(learningRate * (1.0f / batchSize));
    Matrix::Subtract(*weights.get(), *g_weights.get(), *weights.get());
    Matrix::Subtract(*biases.get(), *g_biases.get(), *biases.get());
}