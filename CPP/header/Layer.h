#pragma once

#include "../header/NMath.h"

class Layer {
    
public:

    int inputWidth = 0, outputWidth = 0;
    int inputHeight = 0, outputHeight = 0;
    int inputChannels = 0, outputChannels = 0;

    int outputCount = 0;

    int batchSize = 0;

    std::shared_ptr<Layer> previousLayer;
    std::shared_ptr<Layer> nextLayer;

    bool isOutputLayer = false;
    bool isInputLayer = false;

    std::shared_ptr<Matrix> zOutputs;
    std::shared_ptr<Matrix> aOutputs;
    std::shared_ptr<Matrix> dataIn;

    std::shared_ptr<Matrix> g_Activations;

    ECost networkCost = ECost::MSE;
    EInitialization initializer = EInitialization::Random;
    EDistribution distribution = EDistribution::Uniform;

    Layer() {}

    virtual int GetParameterCount() { return 0; }
    virtual void PrintLayerInformation() { }

    virtual void SetInputShape(int w, int h, int c) {
        inputWidth = w; inputHeight = h; inputChannels = c;
    }

    virtual void SetInputShape(Layer &previousLayer) {
        inputWidth = previousLayer.inputWidth; 
        inputHeight = previousLayer.inputHeight; 
        inputChannels = previousLayer.inputChannels;
    }

    //virtual void SetInputData(std::vector<float> dataIn) {
        
    //}

    virtual void InitializeLayer() {}

    virtual void Evaluate() {}
    virtual void Backpropogation(Matrix &gradients) {}
    virtual void ApplyGradients(float learningRate, int batchSize) {}

};