#include "../header/Testing.h"

void Testing::RunTest() {
    
    std::shared_ptr<Network> network = std::make_shared<Network>();
    network->Dense(50, EActivation::Sigmoid);
    network->Dense(25, EActivation::ReLU);
    network->Dense(10, EActivation::Softmax);
    network->SetInputShape(50, 1, 1);

    network->Compile();

}