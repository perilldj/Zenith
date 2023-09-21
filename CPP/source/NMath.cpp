#include "../header/NMath.h"

// Definitions for random number generation
std::random_device NMath::rd;
std::mt19937 NMath::u_gen(NMath::rd());
std::mt19937 NMath::n_gen(NMath::rd());
std::uniform_real_distribution<float> NMath::u_dis(0.0f, 1.0f);
std::normal_distribution<float> NMath::n_dis(0.0f, 1.0f);

/*
    void NMath::InitializeWeights(EInitialization initializer, EDistribution distribution, Matrix &mat)
    Description: Given a matrix of weights, along with initializer and distribution types, initialize
                 starting weights for the weights given its incoming and outgoing connections derived from the matrix size.
*/

void NMath::InitializeWeights(EInitialization initializer, EDistribution distribution, Matrix &mat) {
    if(distribution == EDistribution::Uniform)
        InitializeUniformWeights(initializer, mat);
    else
        InitializeNormalWeights(initializer, mat);
}

/*
    void NMath::InitializeUniformWeights(EInitlialization initializer, Matrix &mat)
    Description: Initializes weights with a uniform distribution.
*/

void NMath::InitializeUniformWeights(EInitialization initializer, Matrix &mat) {
    float bounds = CalculateInitializerValue(initializer, mat.col, mat.row);
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
            mat.Set(i, j, RandomUniformFloat(-bounds, bounds));
}

/*
    void NMath::InitializeNormalWeights(EInitialization initializer, Matrix &mat)
    Description: Initializes weights with a normal distribution.
*/

void NMath::InitializeNormalWeights(EInitialization initializer, Matrix &mat) {
    float stdDev = CalculateInitializerValue(initializer, mat.col, mat.row);
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetRow(); j++)
            mat.Set(i, j, RandomNormalFloat(0.0f, stdDev));
}

/*
    float NMath::RandomUniformFloat(float lowerBound, float upperBound) 
    Description: Returns a float between the provided bounds, using a uniform distribution.
*/

float NMath::RandomUniformFloat(float lowerBound, float upperBound) {
    return lowerBound + u_dis(u_gen) * (upperBound - lowerBound);
}

/*
    float NMath::RandomNormalFloat(float mean, float stdDev) 
    Description: Returns a random fload from a normal distribution defined by the
                 provided mean and standard deviation. This is the preffered
                 method for weight initialization.
*/

float NMath::RandomNormalFloat(float mean, float stdDev) {
    return mean + n_dis(n_gen) * stdDev;
}

/*
    float NMath::CalculateInitializerValue(EInitialization initializer, int incomingConnections, int outgoingConnections)
    Description: Calculates the respective bounds/standard deviation given a specific initializer type.
*/

float NMath::CalculateInitializerValue(EInitialization initializer, int incomingConnections, int outgoingConnections) {
    
    switch(initializer) {

    case EInitialization::Random :
        return 1.0f;

    case EInitialization::Kaiming :
        return std::sqrt(2.0f / (float) incomingConnections);

    case EInitialization::Xavier :
        return std::sqrt(6.0f / ((float)incomingConnections + (float)outgoingConnections));

    default:
        return 1.0f;

    }

}