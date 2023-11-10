#include "../header/Network.h"

Network::Network() {

}

/*
    void Network::SetInputShape(int d, int r, int c)
    Description: Tells the neural network the shape of the input data.
                        (depth, row, column) = (channels, height, width)
*/

void Network::SetInputShape(int d, int r, int c) {
    inputWidth = c; inputHeight = r; inputChannels = d;
}

/*
    void Network::Evaluate(const py::array_t<float> &input, Matrix &result)
    Description: Evaluates the neural network from the given input, stores the result
                 in the provided "result" matrix passed by reference.
*/

void Network::Evaluate(const py::array_t<float> &input, Matrix &result) {
    layers[0]->SetInputData(input);
    layers[0]->Evaluate();
    Matrix::CopyData(*(layers.back()->aOutputs).get(), result);
}

/*
    void Network::Dense(int nodeCount, EActivation activation)
    Description: Adds a dense layer to the network.
*/

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

/*
    void Network::Compile()
    Description: Compiles the network.
*/

void Network::Compile() {

    currentLearningRate = initialLearningRate;

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

        if(!layers[i]->isInputLayer) {
            layers[i - 1]->nextLayer = layers[i];
            layers[i]->previousLayer = layers[i - 1];
        }

        layers[i]->networkCost = networkCost;
        layers[i]->initializer = networkInitializer;
        layers[i]->distribution = networkDistribution;
        layers[i]->InitializeLayer();

    }

    layers.back()->isOutputLayer = true;

    isNetworkCompiled = true;
    PrintNetworkStructure();
    std::cout << "[INFO] Compilation Successful." << std::endl;

}

/*
    void Network::Train()
    Description: Train the neural network
*/

void Network::Train() {

    std::cout << "[INFO] - Beggining Training..." << std::endl;

    Test(true, false);

    Matrix result = Matrix(*(layers.back()->aOutputs).get());
    Matrix costGradient = Matrix(*(layers.back()->aOutputs).get());
    Matrix oneHotVector = Matrix(*(layers.back()->aOutputs).get());

    int epochCount = 0;
    while(epochCount < totalEpochCount) {

        if(epochCount > totalEpochCount - 4) {
            currentLearningRate = 0.001f;
            std::cout << "dropping learning rate" << std::endl;
            learningRateDecay = false;
        }


        /* Run epoch */
        int batchIndex = 0;
        while(batchIndex < trainingData.size() - batchSize - 1) {

            /* Batch Eval/Backprop */
            for(int i = batchIndex; i < batchIndex + batchSize; i++) {

                oneHotVector.Clear();
                oneHotVector.Set(trainingData[i].label, 1.0f);
                Evaluate(trainingData[i].data, result);
                NMath::CostGradient(networkCost, oneHotVector, result, costGradient);
                layers.back()->Backpropogation(costGradient);

            }

            /* Apply gradients */
            for(int i = 0; i < layers.size(); i++)
                layers[i]->ApplyGradients(currentLearningRate, batchSize);

            batchIndex += batchSize;

            NMath::PrintProgressBar(batchIndex, trainingData.size(), 50);

            if(batchIndex % 15000 == 0)
                Test(false, false);

        }

        NMath::PrintProgressBar(trainingData.size(), trainingData.size(), 50);
        std::cout << std::endl;

        epochCount++;
        //std::random_shuffle(trainingData.begin(), trainingData.end());
        if(learningRateDecay)
            DecayLearningRate(epochCount);

        /* Run test */
        Test(true, false);

    }

    std::cout << "[INFO] - Training Complete." << std::endl;

}

void Network::Test(bool print, bool save) {

    if(print)
        std::cout << "[INFO] - Conducting Test..." << std::endl;

    Matrix result = Matrix(*(layers.back()->aOutputs).get());
    Matrix oneHotVector = Matrix(*(layers.back()->aOutputs).get());

    int correct = 0;
    float cost = 0.0f;
    int d, r, c;

    for(int i = 0; i < trainingData.size(); i++) {

        oneHotVector.Clear();
        oneHotVector.Set(trainingData[i].label, 1.0f);
        Evaluate(trainingData[i].data, result);
        cost += NMath::Cost(networkCost, oneHotVector, result);
        result.MaxElement(d, r, c);
        if(trainingData[i].label == r)
            correct++;

    }

    if(print) {
        std::cout << "[INFO] - Train Results" << std::endl;
        std::cout << "Cost: " << ((float)cost / (float)trainingData.size()) << std::endl;
        std::cout << "Accuracy: " << ((float)correct / (float)trainingData.size()) << std::endl;
    }

    d_training_cost.push_back(((float)cost / (float)trainingData.size()));
    d_training_accuracy.push_back(((float)correct / (float)trainingData.size()));

    correct = 0;
    cost = 0.0f; 

    for(int i = 0; i < testingData.size(); i++) {

        oneHotVector.Clear();
        oneHotVector.Set(testingData[i].label, 1.0f);
        Evaluate(testingData[i].data, result);
        cost += NMath::Cost(networkCost, oneHotVector, result);
        result.MaxElement(d, r, c);
        if(testingData[i].label == r)
            correct++;

    }

    if(print) {
        std::cout << "[INFO] - Test Results" << std::endl;
        std::cout << "Cost: " << ((float)cost / (float)testingData.size()) << std::endl;
        std::cout << "Accuracy: " << ((float)correct / (float)testingData.size()) << std::endl;
    }

    d_testing_cost.push_back(((float)cost / (float)testingData.size()));
    d_testing_accuracy.push_back(((float)correct / (float)testingData.size()));

}

/*
    void Network::AddDatapoint(py::array_t<float> &datapoint, int label)
    Description: Adds a datapoint to the network's training testing pool. Must be
                 done before compiling the network.
*/

void Network::AddDatapoint(py::array_t<float> &datapoint, int label) {
    Datapoint dp = Datapoint(datapoint, label);
    data.push_back(dp);
}

/*
    Network::SplitData()
    Description: Randomly places a datapoint in the training or testing pool,
                 based on the chosen testing training split.
*/

void Network::SplitData() {
    trainingData.clear();
    testingData.clear();
    //std::random_shuffle(data.begin(), data.end());
    int splitIndex = data.size() * trainingTestingSplit;
    for(int i = 0; i < splitIndex; i++)
        trainingData.push_back(data[i]);
    for(int i = splitIndex; i < data.size(); i++)
        testingData.push_back(data[i]);
}

/*
    void Network::DecayLearningRate(int epoch)
    Description: Set the learning rate decayed based on the number of passed epochs.
*/

void Network::DecayLearningRate(int epoch) {
    currentLearningRate = initialLearningRate * (1.0f / (1.0 + decayRate * epoch));
    std::cout << "New Learning Rate: " << currentLearningRate << std::endl;
}

/*
    void Network::PrintNetworkStatus()
    Description: Prints the structure of the network to the screen.
*/

void Network::PrintNetworkStructure() {
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
    std::cout << "Learning Rate: " << currentLearningRate << std::endl;
    if(learningRateDecay)
        std::cout << "Learning Rate Decay: " << decayRate << std::endl;
    std::cout << "Epoch Count: " << totalEpochCount << std::endl;
    std::cout << "Minibatch Size: " << batchSize << std::endl;
    std::cout << "Training Testing Split: " << trainingTestingSplit << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
}

