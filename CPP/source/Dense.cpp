#include "../header/Dense.h"
#include <iomanip>

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
    else
        g_Activations.push_back(std::make_shared<Matrix>(inputHeight, inputWidth));

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

}

void DenseLayer::ApplyGradients(float learningRate) {

}