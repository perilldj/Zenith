#include "../header/Testing.h"

void Testing::RunTest() {
    
    std::shared_ptr<Matrix> inputs = Matrix::CreateMatrix(10, 1);
    std::shared_ptr<Matrix> result = Matrix::CreateMatrix(10, 1);
    NMath::InitializeWeights(EInitialization::Xavier, EDistribution::Normal, *inputs.get());
    NMath::Activation(EActivation::Softmax, *inputs.get(), *result.get());
    
    std::cout << "AA" << std::endl;

}