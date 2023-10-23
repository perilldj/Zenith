#pragma once

#include "../header/Layer.h"

class DenseLayer : public Layer {

public:

    EActivation activation = EActivation::Sigmoid;

    std::shared_ptr<Matrix> weights;
    std::shared_ptr<Matrix> g_weights;
    std::shared_ptr<Matrix> biases;
    std::shared_ptr<Matrix> g_biases;

    DenseLayer();

    virtual void InitializeLayer() override;

    virtual int GetParameterCount() override;
    virtual void PrintLayerInformation() override;

    virtual void Evaluate() override;
    virtual void Backpropogation(Matrix &gradients) override;
    virtual void ApplyGradients(float learningRate) override;

};