#pragma once

#include <cmath>
#include <random>
#include <algorithm>
#include <Map>
#include "../header/Matrix.h"

enum EInitialization {
    Random,
    Kaiming,
    Xavier
};



enum EDistribution {
    Uniform,
    Normal
};

enum EActivation {
    Identity,
    Sigmoid,
    Tanh,
    ReLU,
    LeakyReLU,
    SiLU,
    Softplus,
    Softmax
};

inline std::ostream &operator<<(std::ostream &os, EActivation activation) {
    const std::map<EActivation, const char*> EnumTable {
        {EActivation::Identity, "Identity"},
        {EActivation::Sigmoid, "Sigmoid"},
        {EActivation::Tanh, "Tanh"},
        {EActivation::ReLU, "ReLU"},
        {EActivation::LeakyReLU, "Leaky ReLU"},
        {EActivation::SiLU, "SiLU"},
        {EActivation::Softplus, "Softplus"},
        {EActivation::Softmax, "Softmax"}
    };
    auto it = EnumTable.find(activation);
    os << (it == EnumTable.end() ? "[ERROR] - Enum value not found." : it->second);
    return os;
}

enum ECost {
    MSE,
    CrossEntropy
};

enum ELayer {
    Dense,
    Conv2D,
    MaxPooling,
    MeanPooling,
    Dropout,
    Flatten
};

class NMath {

public:

    static void EvaluateFunctionOverMatrix(float (*func)(const float&), Matrix &mat, Matrix &out);

    static void dCdz(ECost cost, EActivation activation, bool isOutputLayer, Matrix &gradients, 
                     Matrix &aOutputs, Matrix &zOutputs, Matrix &result);

    static void Activation(EActivation activation, Matrix &mat, Matrix &out);
    static void ActivationGradient(EActivation activation, Matrix &mat, Matrix &out);

    static float Cost(ECost cost, Matrix &expected, Matrix &actual);
    static void CostGradient(ECost cost, Matrix &expected, Matrix &actual, Matrix &out);

    static float RandomUniformFloat(float lowerBound, float upperBound);
    static float RandomNormalFloat(float mean, float stdDev);

    static void InitializeWeights(EInitialization initializer, EDistribution distribution, Matrix &mat);

private:

    static void InitializeUniformWeights(EInitialization initializer, Matrix &mat);
    static void InitializeNormalWeights(EInitialization initializer, Matrix &mat);

    static float CalculateInitializerValue(EInitialization initializer, int incomingConnections, int outgoingConnections);

    static void PrintProgressBar(float progress, float total, int width);

    static std::random_device rd;
    static std::mt19937 u_gen;
    static std::mt19937 n_gen;
    static std::uniform_real_distribution<float> u_dis;
    static std::normal_distribution<float> n_dis;

};