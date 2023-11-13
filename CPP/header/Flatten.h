#pragma once

#include "../header/Layer.h"

class FlattenLayer : public Layer {

public:

    FlattenLayer();

    std::shared_ptr<Matrix> g_Activations;

    virtual void InitializeLayer() override;

    virtual int GetParameterCount() override;
    virtual void PrintLayerInformation() override;

    virtual void Evaluate() override;
    virtual void Backpropagation(Matrix &gradients) override;

private:

    void FlattenMatrix(Matrix &mat, Matrix &out);
    void RebuildMatrix(Matrix &mat, Matrix &out);

};