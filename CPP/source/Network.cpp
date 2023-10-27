#include "../header/Network.h"

Network::Network() {

}

void Network::SetInputShape(int d, int r, int c) {
    inputWidth = c; inputHeight = r; inputChannels = d;
}

void Network::Evaluate(const py::array_t<float> &input, Matrix &result) {
    layers[0]->SetInputData(input);
    layers[0]->Evaluate();
    Matrix::CopyData(*(layers.back()->aOutputs).get(), result);
}

void Network::Dense(int nodeCount, EActivation activation) {
    std::shared_ptr<DenseLayer> layer = std::make_shared<DenseLayer>();
    if(layers.empty())
        layer->isInputLayer = true;
    else
        layer->previousLayer = layers.back();
    layer->activation = activation;
    layer->outputCount = nodeCount;
    layers.push_back(std::static_pointer_cast<Layer, DenseLayer>(layer));
    layerTypes.push_back(ELayer::Dense);
}

void Network::Compile() {

    std::cout << "\n[INFO] Compiling Network..." << std::endl;
    if(disableCompilation)
        return;

    if(layerTypes.back() != ELayer::Dense) {
        std::cout << "Compile [ERROR] - Last layer must be a DenseLayer." << std::endl;
        disableCompilation = true;
        return;
    }

    std::shared_ptr<DenseLayer> lastLayer = std::static_pointer_cast<DenseLayer, Layer>(layers.back());
    if(networkCost == ECost::CrossEntropy && lastLayer->activation != EActivation::Softmax) {
        std::cout << "Compile [ERROR] - When using the cross entropy cost function the last layer's" <<
                     " activation function must be Softmax." << std::endl;
        disableCompilation = true;
        return;
    }

    SplitData();

    for(int i = 0; i < layers.size(); i++) {

        if(layers[i]->isInputLayer)
            layers[i]->SetInputShape(inputWidth, inputHeight, inputChannels);
        else
            layers[i]->SetInputShape(*layers[i - 1].get());

        layers[i]->InitializeLayer();
        layers[i]->networkCost = networkCost;
        layers[i]->initializer = networkInitializer;
        layers[i]->distribution = networkDistribution;

    }

    isNetworkCompiled = true;
    PrintNetworkStatus();
    std::cout << "[INFO] Compilation Successful." << std::endl;

}

void Network::AddDatapoint(py::array_t<float> &datapoint, int label) {
    Datapoint dp = Datapoint(datapoint, label);
    data.push_back(dp);
}

void Network::SplitData() {
    trainingData.clear();
    testingData.clear();
    std::random_shuffle(data.begin(), data.end());
    int splitIndex = data.size() * trainingTestingSplit;
    for(int i = 0; i < splitIndex; i++)
        trainingData.push_back(data[i]);
    for(int i = splitIndex; i < data.size(); i++)
        testingData.push_back(data[i]);
}

void Network::PrintNetworkStatus() {
    std::cout << "--------------- NETWORK STRUCTURE ---------------" << std::endl;
    std::cout << "Layer Type         Activation        Param Count " << std::endl;
    std::cout << "Input              N/A               0" << std::endl;
    int count = 0;
    for(int i = 0; i < layers.size(); i++) {
        layers[i]->PrintLayerInformation();
        count += layers[i]->GetParameterCount();
    }
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Total Parameter Count:  " << count << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Cost Function: " << networkCost << std::endl;
    std::cout << "Weight Initializer: " << networkInitializer << std::endl;
    std::cout << "Weight Distribution: " << networkDistribution << std::endl;
    std::cout << "Learning Rate: " << initialLearningRate << std::endl;
    if(learningRateDecay)
        std::cout << "Learning Rate Decay: " << decayRate << std::endl;
    std::cout << "Epoch Count: " << totalEpochCount << std::endl;
    std::cout << "Minibatch Size: " << batchSize << std::endl;
    std::cout << "Training Testing Split: " << trainingTestingSplit << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
}

