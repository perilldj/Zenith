#include "../header/Dense.h"

DenseLayer::DenseLayer() {

}

void DenseLayer::InitializeLayer() {

    weights = std::make_shared<Matrix>(outputCount, inputWidth);
    g_weights = std::make_shared<Matrix>(outputCount, inputWidth);
    biases = std::make_shared<Matrix>(outputCount, 1);
    g_biases = std::make_shared<Matrix>(outputCount, inputWidth);

    zOutputs = std::make_shared<Matrix>(outputCount, 1);
    aOutputs = std::make_shared<Matrix>(outputCount, 1);

    if(isInputLayer)
        dataIn = std::make_shared<Matrix>(inputWidth, 1);

    NMath::InitializeWeights(initializer, distribution, *weights.get());

}

int DenseLayer::GetParameterCount() {
    int count = 0;
    count += weights->GetCol() *  weights->GetRow();
    count += biases->GetCol() * weights->GetRow();
    return count;
}

void DenseLayer::PrintLayerInformation() {
    std::cout << "Dense\t\t\t" << GetParameterCount() << std::endl;
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

}

void DenseLayer::ApplyGradients(float learningRate) {

}