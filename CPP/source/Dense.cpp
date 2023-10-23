#include "../header/Dense.h"

DenseLayer::DenseLayer() {

}

void DenseLayer::InitializeLayer() {

    weights = std::make_shared<Matrix>(outputCount, inputWidth);
    g_weights = std::make_shared<Matrix>(outputCount, inputWidth);
    biases = std::make_shared<Matrix>(1, outputCount);
    g_biases = std::make_shared<Matrix>(outputCount, inputWidth);

    zOutputs = std::make_shared<Matrix>(1, outputCount);
    aOutputs = std::make_shared<Matrix>(1, outputCount);

    if(isInputLayer)
        dataIn = std::make_shared<Matrix>(1, inputWidth);

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

}

void DenseLayer::Backpropogation(Matrix &gradients) {

}

void DenseLayer::ApplyGradients(float learningRate) {

}