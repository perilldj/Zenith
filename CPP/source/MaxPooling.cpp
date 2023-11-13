#include "../header/MaxPooling.h"
#include <iomanip>

#define FILTER_SIZE 2

MaxPoolingLayer::MaxPoolingLayer() { }

/*
    void MaxPoolingLayer::InitializeLayer()
    Description: Initializes the max pooling layer.
*/

void MaxPoolingLayer::InitializeLayer() {

    outputChannels = inputChannels;
    outputWidth = std::ceil(inputWidth / 2.0f);
    outputHeight = std::ceil(inputHeight / 2.0f);

    aOutputs = Matrix::CreateMatrix(outputChannels, outputHeight, outputWidth);
    aOutputsTranspose = Matrix::C_Transpose(*aOutputs.get());
    maxLocations.reserve(outputChannels * outputHeight * outputWidth);
    g_Activations = Matrix::CreateMatrix(inputChannels, inputHeight, inputWidth);

    outputCount = outputChannels * outputHeight * outputWidth;

    if(isInputLayer)
        dataIn = Matrix::CreateMatrix(inputChannels, inputHeight, inputWidth);

}

/*
    int MaxPoolingLayer::GetParameterCount()
    Description: Returns the total number of parameters in this layer.
*/

int MaxPoolingLayer::GetParameterCount() {
    return 0;
}

/*
    void MaxPoolingLayer::PrintLayerInformation()
    Description: Prints the name of the layer, the activation function, and
                 the number of parameters to the screen, properly spaced with
                 respect to Network::PrintNetworkStructure() function.
*/

void MaxPoolingLayer::PrintLayerInformation() {
    std::stringstream ss;
    ss << "(" << outputChannels << ", " << outputHeight << ", " << outputWidth << ")";
    std::cout << std::left << std::setw(19) << "MaxPooling" 
              << std::setw(18) << ss.str()
              << std::setw(18) << "N/A" << std::setw(18) << GetParameterCount() << std::endl;
}

/*
    void MaxPoolingLayer::Evaluate()
    Description: Evaluates the current layer based on the output of the previous layer.
                 If this layer is the first in the network, the data is fetched
                 from the dataIn matrix.
*/

void MaxPoolingLayer::Evaluate() {

    maxLocations.clear();
    aOutputs->Clear();

    if(isInputLayer)
        for(int i = 0; i < inputChannels; i++)
            MaxPoolingOnChannel(dataIn, i);
    else
        for(int i = 0; i < inputChannels; i++)
            MaxPoolingOnChannel(previousLayer->aOutputs, i);

    if(nextLayer)
        nextLayer->Evaluate();

}

/*
    void MaxPoolingLayer::Backpropagation(Matrix &gradients)
    Description: Calculates the gradients based on the provided change of cost
                 with respect to the activation output. In the case of a max pooling
                 layer, the gradients are just passed on the the previously calculated
                 max value locations.
*/

void MaxPoolingLayer::Backpropagation(Matrix &gradients) {

    if(isInputLayer)
        return;

    g_Activations->Clear();
    int index = 0;
    for(int i = 0; i < gradients.GetDepth(); i++)
        for(int j = 0; j < gradients.GetRow(); j++)
            for(int k = 0; k < gradients.GetCol(); k++)
                g_Activations->Set(std::get<0>(maxLocations[index]),
                                   std::get<1>(maxLocations[index]),       
                                   std::get<2>(maxLocations[index]),  
                                   gradients.Get(i, j, k));

    if(previousLayer)
        previousLayer->Backpropagation(*g_Activations.get());

}

/*
    void MaxPoolingLayer::MaxPoolingOnChannel(int channel);
    Description: Performs max pooling on a single channel.
*/

void MaxPoolingLayer::MaxPoolingOnChannel(std::shared_ptr<Matrix> &input, int channel) {
    
    if(channel < 0 || channel >= inputChannels)
        return;

    for(int i = 0; i < input->GetRow(); i += FILTER_SIZE)
        for(int j = 0; j < input->GetCol(); j += FILTER_SIZE)
            FindMax(input, channel, i, j);

}

/*

    void MaxPoolingLayer::FindMax(std::shared_ptr<Matrix> &input, int channel, int filterY, int filterX)
    Description: Finds the maximum value in a defined area and sets it to it's respective location in the
                 max pooling layer's output.

*/

void MaxPoolingLayer::FindMax(std::shared_ptr<Matrix> &input, int channel, int filterY, int filterX) {

    int c = 0, r = 0;
    float max = input->Get(channel, filterY, filterX);
    for(int i = filterY; i < FILTER_SIZE + filterY; i++) {
        for(int j = filterX; j < FILTER_SIZE + filterX; j++) {
            if(!input->IsLocationInBounds(channel, i, j))
                continue;
            if(input->Get(channel, i, j) > max) {
                max = input->Get(channel, i, j);
                r = i / 2; c = j / 2;
            }
        }
    }

    aOutputs->Set(channel, r, c, max);
    maxLocations.push_back(std::tuple<int, int, int>(channel, filterY, filterX));

}