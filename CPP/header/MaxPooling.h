#pragma once

#include "../header/Layer.h"

class MaxPoolingLayer : public Layer {

public:

    std::vector<std::tuple<int, int, int>> maxLocations;

    MaxPoolingLayer();

    virtual void InitializeLayer() override;

    virtual int GetParameterCount() override;
    virtual void PrintLayerInformation() override;

    virtual void Evaluate() override;
    virtual void Backpropagation(Matrix &gradients) override;

private:

    void MaxPoolingOnChannel(std::shared_ptr<Matrix> &input, int channel);
    void FindMax(std::shared_ptr<Matrix> &input, int channel, int filterY, int filterX);

};