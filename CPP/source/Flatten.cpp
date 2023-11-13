#include "../header/Flatten.h"
#include <iomanip>

FlattenLayer::FlattenLayer() { }

/*
    void FlattenLayer::InitializeLayer()
    Description: Initializes the flatten layer, creating properly sized matrices with
                 respect to the input shape and output count.
*/

void FlattenLayer::InitializeLayer() {
    outputChannels = 1;
    outputHeight = inputChannels * inputWidth * inputHeight;
    outputWidth = 1;

    aOutputs = Matrix::CreateMatrix(outputChannels, outputHeight, outputWidth);
    aOutputsTranspose = Matrix::C_Transpose(*aOutputs.get());
    g_Activations = Matrix::CreateMatrix(inputChannels, inputHeight, inputWidth);

    if(isInputLayer)
        dataIn = Matrix::CreateMatrix(inputChannels, inputHeight, inputWidth);

}

/*
    int FlattenLayer::GetParameterCount()
    Description: Returns the total number of parameters in this layer.
*/

int FlattenLayer::GetParameterCount() {
    return 0;
}

/*
    void FlattenLayer::PrintLayerInformation()
    Description: Prints the name of the layer, the activation function, and
                 the number of parameters to the screen, properly spaced with
                 respect to Network::PrintNetworkStructure() function.
*/

void FlattenLayer::PrintLayerInformation() {
    std::stringstream ss;
    ss << "(" << outputChannels << ", " << outputHeight << ", " << outputWidth << ")";
    std::cout << std::left << std::setw(19) << "Flatten" 
                           << std::setw(18) << ss.str()
                           << std::setw(18) << "N/A" 
                           << std::setw(18) << GetParameterCount() << std::endl;
}

/*
    void FlattenLayer::Evaluate()
    Description: Evaluates the current layer based on the output of the previous layer.
                 If this layer is the first in the network, the data is fetched
                 from the dataIn matrix.
*/

void FlattenLayer::Evaluate() {

    if(!isInputLayer)
        FlattenMatrix(*(previousLayer->aOutputs).get(), *aOutputs.get());
    else
        FlattenMatrix(*dataIn.get(), *aOutputs.get());

    if(nextLayer)
        nextLayer->Evaluate();

}

/*
    void FlattenLayer::Backpropagation(Matrix &gradients)
    Description: Calculates the gradients based on the provided change of cost
                 with respect to the activation output.
*/

void FlattenLayer::Backpropagation(Matrix &gradients) {

    if(isInputLayer)
        return;

    RebuildMatrix(gradients, *g_Activations.get());
    if(previousLayer)
        previousLayer->Backpropagation(*g_Activations.get());

}

/*
    void FlattenLayer::FlattenMatrix(Matrix &mat, Matrix &out);
    Description: Flattens a multidimensional matrix into a one-dimensional matrix.
*/

void FlattenLayer::FlattenMatrix(Matrix &mat, Matrix &out) {

    int index = 0;
    for(int i = 0; i < mat.GetDepth(); i++)
        for(int j = 0; j < mat.GetRow(); j++)
            for(int k = 0; k < mat.GetCol(); k++) {
                out.Set(index, mat.Get(i, j, k));
                index++;
            }

}

/*
    void FLattenLayer::RebuildMatrix(Matrix &mat, Matrix &out)
    Description: Rebuilds a flattened matrix into a provided multidimensional matrix.
*/

void FlattenLayer::RebuildMatrix(Matrix &mat, Matrix &out) {

    int index = 0;
    for(int i = 0; i < out.GetDepth(); i++)
        for(int j = 0; j < out.GetRow(); j++)
            for(int k = 0; k < out.GetCol(); k++) {
                out.Set(i, j, k, mat.Get(index));
                index++;
            }

}