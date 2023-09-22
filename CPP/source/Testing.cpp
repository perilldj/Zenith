#include "../header/Testing.h"

void Testing::RunTest() {
    
    std::shared_ptr<Matrix> inputs = Matrix::CreateMatrix(10, 1);
    std::shared_ptr<Matrix> expected = Matrix::CreateMatrix(10, 1);
    std::shared_ptr<Matrix> result = Matrix::CreateMatrix(10, 1);
    expected->Set(5, 0, 1.0f);
    NMath::InitializeWeights(EInitialization::Xavier, EDistribution::Normal, *inputs.get());
    std::cout << NMath::Cost(ECost::CrossEntropy, *expected.get(), *inputs.get()) << std::endl;
    NMath::CostGradient(ECost::CrossEntropy, *expected.get(), *inputs.get(), *result.get());
    
    std::cout << "AA" << std::endl;

}