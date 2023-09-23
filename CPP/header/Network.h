#pragma once

#include "../header/Layer.h"

class Network {

public:

    bool learningRateDecay = false;
    float initialLearningRate = 1.0f;
    float currentLearningRate = initialLearningRate;
    float decayRate = 0.1f;

    bool isNetworkCompiled = false;
    bool disableCompilation = false;

    ECost networkCost = ECost::MSE;
    EInitialization networkInitializer = EInitialization::Random;
    EDistribution networkDistribution = EDistribution::Normal;

    std::vector<std::shared_ptr<Layer>> layers;
    std::vector<ELayer> layerTypes;

    Network();

    void Evaluate(Matrix &result);
    void SetInput(Matrix &input);

    void TrainNetwork();
    void TestNetwork(bool print, bool save);

    void DefineInputShape(int inputWidth, int inputHeight, int inputChannels);

    void Compile();

    void AddTrainingDatapoint(py::array_t<float> &data, int label);
    void AddTestingDatapoint(py::array_t<float> &data, int label);

    void DecayLearningRate(int epoch);

private:

};