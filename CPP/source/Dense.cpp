#include "../header/Dense.h"
#include <iomanip>

DenseLayer::DenseLayer() {

}

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

int DenseLayer::GetParameterCount() {
    int count = 0;
    count += weights->GetCol() *  weights->GetRow();
    count += biases->GetCol() * weights->GetRow();
    return count;
}

void DenseLayer::PrintLayerInformation() {
    std::cout << std::left << std::setw(19) << "Dense" << std::setw(18) << activation 
                           << std::setw(18) << GetParameterCount() << std::endl;
}

void DenseLayer::Evaluate() {
    if(isInputLayer)
        Matrix::Product(*weights.get(), *dataIn.get(), *zOutputs.get());
    else
        Matrix::Product(*weights.get(), *(previousLayer->aOutputs.get()), *zOutputs.get());
    Matrix::Add(*zOutputs.get(), *biases.get(), *zOutputs.get());
    NMath::Activation(activation, *zOutputs.get(), *aOutputs.get());
    nextLayer->Evaluate();
}

void DenseLayer::Backpropogation(Matrix &gradients) {
    
    if(isInputLayer)
        return;

    Matrix dCdz = Matrix(gradients.GetCol(), gradients.GetRow());
    NMath::dCdz(networkCost, activation, isOutputLayer, 
                gradients, *aOutputs.get(), *zOutputs.get(), dCdz);

    Matrix::Transpose(*aOutputs.get(), *aOutputsTranspose.get());
    Matrix::AccumulateProduct(dCdz, *aOutputsTranspose.get(), *g_weights.get());
    Matrix::Add(*g_biases.get(), dCdz, *g_biases.get());
    Matrix::Product(*weightsTranspose.get(), dCdz, *g_Activations.get());
    previousLayer->Backpropogation(*g_Activations.get());

}

void DenseLayer::ApplyGradients(float learningRate, int batchSize) {
    g_weights->Scale(learningRate * (1.0f / batchSize));
    g_biases->Scale(learningRate * (1.0f / batchSize));
    Matrix::Subtract(*weights.get(), *g_weights.get(), *weights.get());
    Matrix::Subtract(*biases.get(), *g_biases.get(), *biases.get());
}