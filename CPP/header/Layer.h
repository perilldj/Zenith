#pragma once

#include "../header/NMath.h"

class Layer {
    
    int outputWidth = 0;
    int outputHeight = 0;
    int outputChannels = 0;

    int batchSize = 0;

    std::shared_ptr<Layer> previousLayer;
    std::shared_ptr<Layer> nextLayer;

    bool isOutputLayer = false;
    bool isInputLayer = false;

    std::shared_ptr<Matrix> aOutputs;
    std::shared_ptr<Matrix> dataIn;

    Layer() {}

    virtual int GetParameterCount() { }
    virtual void PrintLayerInformation() { }

    virtual void Evaluate() {}
    virtual void Backpropogation(Matrix &gradients) {}
    virtual void ApplyGradients(float learningRate);

};