#pragma once

#include <pybind11/numpy.h>

#include "../header/Layer.h"
#include "../header/Dense.h"
#include "../header/Datapoint.h"

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

    int totalEpochCount = 1;
    int batchSize = 10;
    float trainingTestingSplit = 0.8f;

    ECost networkCost = ECost::MSE;
    EInitialization networkInitializer = EInitialization::Random;
    EDistribution networkDistribution = EDistribution::Normal;

    std::vector<std::shared_ptr<Layer>> layers;
    std::vector<ELayer> layerTypes;

    Network();

    void SetInputShape(int d, int r, int c);

    void Evaluate(const py::array_t<float> &data, Matrix &result);

    void TrainNetwork();
    void TestNetwork(bool print, bool save);

    void Dense(int nodeCount, EActivation activation);

    void Compile();

    void AddDatapoint(py::array_t<float> &datapoint, int label);

    void DecayLearningRate(int epoch);

private:

    std::vector<Datapoint> data;
    std::vector<Datapoint> trainingData;
    std::vector<Datapoint> testingData;

    void SplitData();
    void PrintNetworkStatus();


};