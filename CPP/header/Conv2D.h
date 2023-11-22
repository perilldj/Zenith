#pragma once

#include "../header/Layer.h"

class Conv2DLayer : public Layer {

public:

    EActivation activation = EActivation::Sigmoid;

    std::vector<std::shared_ptr<Matrix>> kernels;
    std::vector<std::shared_ptr<Matrix>> g_kernels;
    std::vector<std::shared_ptr<Matrix>> rotatedKernels;

    std::shared_ptr<Matrix> biases;
    std::shared_ptr<Matrix> g_biases;

    std::shared_ptr<Matrix> dCdz;

    int kernelSize = 3;
    int kernelCount = 1;

    Conv2DLayer();

    virtual void InitializeLayer() override;

    virtual int GetParameterCount() override;
    virtual void PrintLayerInformation() override;

    virtual void Evaluate() override;
    virtual void Backpropagation(Matrix &gradients) override;
    virtual void ApplyGradients(float learningRate, int batchSize) override;

private:

    void CalculateBiasGradients();
    float AccumulateChannel(Matrix &mat, int channel);
    void RotateKernels();
    void AddBiases();
    void AddBiasToChannel(Matrix &mat, int channel, float bias);

};