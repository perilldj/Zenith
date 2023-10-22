#pragma once

#include <pybind11/numpy.h>

#include "../header/Layer.h"
#include "../header/Dense.h"

namespace py = pybind11;

class Network {

public:

    bool learningRateDecay = false;
    float initialLearningRate = 1.0f;
    float currentLearningRate = initialLearningRate;
    float decayRate = 0.1f;

    bool isNetworkCompiled = false;
    bool disableCompilation = false;

    int inputWidth = 0, inputHeight = 0, inputChannels = 0;

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

    void Dense(int nodeCount, EActivation activation);

    void Compile();

    void AddTrainingDatapoint(py::array_t<float> &data, int label);
    void AddTestingDatapoint(py::array_t<float> &data, int label);

    void DecayLearningRate(int epoch);

private:

};