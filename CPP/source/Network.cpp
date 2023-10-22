#include "../header/Network.h"

Network::Network() {

}

void Network::Compile() {

    if(disableCompilation)
        return;

    if(layerTypes.back() != ELayer::Dense) {
        std::cout << "Network::Compile [ERROR] - Last layer must be a DenseLayer." << std::endl;
        disableCompilation = true;
        return;
    }

    std::shared_ptr<DenseLayer> lastLayer = std::static_pointer_cast<DenseLayer, Layer>(layers.back());
    if(networkCost == ECost::CrossEntropy && lastLayer->activation != EActivation::Softmax) {
        std::cout << "Network::Compile [ERROR] - When using the cross entropy cost function the last layer's" <<
                     " activation function must be Softmax." << std::endl;
        disableCompilation = true;
        return;
    }

    for(int i = 0; i < layers.size(); i++) {

        if(layers[i]->isInputLayer)
            layers[i]->SetInputShape(inputWidth, inputHeight, inputChannels);
        else
            layers[i]->SetInputShape(*layers[i - 1].get());

        layers[i]->InitializeLayer();

    }

    isNetworkCompiled = true;

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