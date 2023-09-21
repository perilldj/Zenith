#pragma once

#include <cmath>
#include <random>
#include <algorithm>
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

enum ECost {
    MSE,
    CrossEntropy
};

enum ELayer {
    Empty,
    Dense,
    Conv2D,
    MaxPooling,
    MeanPooling,
    Dropout
};

class NMath {

public:

    //static void Activation();
    //static void ActivationDerivative();

    //static void Cost();
    //static void CostDerivative();

    static float RandomUniformFloat(float lowerBound, float upperBound);
    static float RandomNormalFloat(float mean, float stdDev);

    static void InitializeWeights(EInitialization initializer, EDistribution distribution, Matrix &mat);

private:

    static void InitializeUniformWeights(EInitialization initializer, Matrix &mat);
    static void InitializeNormalWeights(EInitialization initializer, Matrix &mat);

    static float CalculateInitializerValue(EInitialization initializer, int incomingConnections, int outgoingConnections);

    static std::random_device rd;
    static std::mt19937 u_gen;
    static std::mt19937 n_gen;
    static std::uniform_real_distribution<float> u_dis;
    static std::normal_distribution<float> n_dis;

};