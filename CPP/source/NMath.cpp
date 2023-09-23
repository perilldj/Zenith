#include "../header/NMath.h"

// Definitions for random number generation
std::random_device NMath::rd;
std::mt19937 NMath::u_gen(NMath::rd());
std::mt19937 NMath::n_gen(NMath::rd());
std::uniform_real_distribution<float> NMath::u_dis(0.0f, 1.0f);
std::normal_distribution<float> NMath::n_dis(0.0f, 1.0f);

/*
    void NMath::EvaluateFunctionOverMatrix(float (*func)(const float&), Matrix &mat, Matrix &out)
    Description: Given a function pointer that takes a const float reference and returns a float, the
                 provided function is then applied on every element in the given matrix, storing
                 the respective result in the provided "out" matrix passed by refernece.
*/

void NMath::EvaluateFunctionOverMatrix(float (*func)(const float&), Matrix &mat, Matrix &out) {
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
            out.Set(i, j, func(mat.Get(i, j)));
}

/*
    void NMath::Activation(EActivation activation, Matrix &mat, Matrix &out)
    Description: Applies the given activation function to all elements in mat and stores the output
                 in the provided "out" matrix passed by reference.
*/

void NMath::Activation(EActivation activation, Matrix &mat, Matrix &out) {

    if(mat.GetCol() == out.GetCol() && mat.GetRow() == out.GetCol()) {
        std::cout << "NMath.cpp - [ERROR] - Activation function input and output matrices are of different sizes." << std::endl;
        return;
    }

    switch(activation) {

    case EActivation::Identity :
        break;
    case EActivation::Sigmoid :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return (1.0f / (1.0f + std::exp(-x))); }, mat, out);
        break;
    case EActivation::Tanh :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return std::tanh(x); }, mat, out);
        break;
    case EActivation::ReLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return (x > 0.0f) ? x : 0.0f; }, mat, out);
        break;
    case EActivation::LeakyReLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return (x > 0.0f) ? x : 0.01f * x; }, mat, out);
        break;
    case EActivation::SiLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return x * (1.0f / (1.0f + std::exp(-x))); }, mat, out);
        break;
    case EActivation::Softplus :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return std::log(1.0f + std::exp(x)); }, mat, out);
        break;
    case EActivation::Softmax :
        
        if(mat.GetCol() > 1) {
            std::cout << "NMath.cpp - [ERROR] - The softmax activation function is used on matrices with only 1 column." << std::endl;
            return;
        }

        float maxVal = mat.MaxElement();
        float sumExp = 0.0f;
        for(int i = 0; i < mat.GetRow(); i++) {
            out.Set(i, 0, std::exp(mat.Get(i, 0) - maxVal));
            sumExp += out.Get(i, 0);
        }

        float epsilon = 1e-4;
        for(int i = 0; i < out.GetRow(); i++)
            out.Set(i, 0, out.Get(i, 0) / (sumExp + epsilon));
        break;

    }

}

/*
    void NMath::ActivationGradient(EActivation activation, Matrix &mat, Matrix &out)
        Description: Applies the given activation gradient function to all elements in mat and stores the output
                     in the provided "out" matrix passed by reference.
*/

void NMath::ActivationGradient(EActivation activation, Matrix &mat, Matrix &out) {

    if(mat.GetCol() == out.GetCol() && mat.GetRow() == out.GetCol()) {
        std::cout << "NMath.cpp - [ERROR] - Activation gradient input and output matrices are of different sizes." << std::endl;
        return;
    }

    switch(activation) {

    case EActivation::Identity :
        out.Clear();
        break;
    case EActivation::Sigmoid :
        EvaluateFunctionOverMatrix([](const float &x) -> float { float sigmoid = (1.0f / (1.0f + std::exp(-x)));
                                                                 return sigmoid * (1 - sigmoid); }, mat, out);
        break;
    case EActivation::Tanh :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return 1.0f - std::pow(std::tanh(x), 2); }, mat, out);
        break;
    case EActivation::ReLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return (x > 0.0f) ? 1.0f : 0.0f; }, mat, out);
        break;
    case EActivation::LeakyReLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return (x > 0.0f) ? 1.0f : 0.01f; }, mat, out);
        break;
    case EActivation::SiLU :
        EvaluateFunctionOverMatrix([](const float &x) -> float { float sigmoid = (1.0f / (1.0f + std::exp(-x)));
                                                                 float dSigmoid = sigmoid * (1 - sigmoid);
                                                                 return sigmoid + x * dSigmoid; }, mat, out);
        break;
    case EActivation::Softplus :
        EvaluateFunctionOverMatrix([](const float &x) -> float { return(1.0f / (1.0f + std::exp(-x))); }, mat, out);
        break;
    case EActivation::Softmax :

        if(mat.GetCol() > 1) {
            std::cout << "NMath.cpp - [ERROR] - The softmax gradient function is used on matrices with only 1 column." << std::endl;
            return;
        }

        float expSum = 0.0f;
        for(int i = 0; i < mat.GetRow(); i++) {
            expSum += std::exp(mat.Get(i, 0));
        }

        float exp = 0.0f;
        for(int i = 0; i < mat.GetRow(); i++) {
            exp = std::exp(mat.Get(i, 0));
            out.Set(i, 0, (exp * expSum - exp * exp) / (expSum * expSum));
        }
        break;

    }

}

/*
    float NMath::Cost(ECost cost, Matrix &expected, Matrix &actual)
    Description: Calculates the total cost of a matrix with it's expected result.
*/

float NMath::Cost(ECost cost, Matrix &expected, Matrix &actual) {

    if(!Matrix::IsEqualSize(expected, actual)) {
        std::cout << "NMath.cpp - [ERROR] - Cost function matrices sizes are of different sizes." << std::endl;
        return -1.0f;
    }

    float result = 0.0f;

    switch (cost) {

    case ECost::MSE :
        
        for(int i = 0; i < actual.GetRow(); i++)
            for(int j = 0; j < actual.GetCol(); j++)
                result += std::pow(actual.Get(i, j) - expected.Get(i, j), 2);
        break;

    case ECost::CrossEntropy :

        for(int i = 0; i < expected.GetRow(); i++)
            for(int j = 0; j < expected.GetCol(); j++)
                if(expected.Get(i, j) == 1.0f)
                    result += -std::log(actual.Get(i, j));
        break;

    }

    return result;

}

/*
    void NMath::CostGradient(ECost cost, Matrix &mat, Matrix &out)
    Description: Calculates the cost gradient matrix from the expected and actual cost values.
                 The result is stored in the provided "out" matrix passed by reference.
*/
    
void NMath::CostGradient(ECost cost, Matrix &expected, Matrix &actual, Matrix &out) {

    if(!Matrix::IsEqualSize(expected, actual) && !Matrix::IsEqualSize(actual, out)) {
        std::cout << "NMath.cpp - [ERROR] - Cost gradient matrices sizes are of different sizes." << std::endl;
        return;
    }

    switch(cost) {

    case ECost::MSE :

        for(int i = 0; i < actual.GetRow(); i++)
            for(int j = 0; j < actual.GetCol(); j++)
                out.Set(i, j, 2.0f * (actual.Get(i, j) - expected.Get(i, j)));
        break;

    case ECost::CrossEntropy :
    
        for(int i = 0; i < actual.GetRow(); i++)
            for(int j = 0; j < actual.GetCol(); j++)
                out.Set(i, j, expected.Get(i, j));

    }

}

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
    float bounds = CalculateInitializerValue(initializer, mat.GetCol(), mat.GetRow());
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
            mat.Set(i, j, RandomUniformFloat(-bounds, bounds));
}

/*
    void NMath::InitializeNormalWeights(EInitialization initializer, Matrix &mat)
    Description: Initializes weights with a normal distribution.
*/

void NMath::InitializeNormalWeights(EInitialization initializer, Matrix &mat) {
    float stdDev = CalculateInitializerValue(initializer, mat.GetCol(), mat.GetRow());
    for(int i = 0; i < mat.GetRow(); i++)
        for(int j = 0; j < mat.GetCol(); j++)
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
        return std::sqrt(6.0f / ((float) incomingConnections + (float) outgoingConnections));

    default:
        return 1.0f;

    }

}

/*
    void NMath::PrintProgressBar(float progress, float total, int width);
    Description: Print progress bar to current line, print a \n when done with the progress bar.
*/

void NMath::PrintProgressBar(float progress, float total, int width) {

    float ratio = progress / total;
    int barWidth = (int)(ratio * width);

    std::cout << "[";
    for (int i = 0; i < width; i++) {
        if (i < barWidth)
            std::cout << "=";
        else if (i == barWidth)
            std::cout << ">";
        else
            std::cout << " ";
    }

    std::cout << "] " << (int)(ratio * 100.0) << "%\r";
    std::cout.flush();

}