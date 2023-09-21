#include "../header/Testing.h"

void Testing::RunTest() {
    
    std::shared_ptr<Matrix> inputs = Matrix::CreateMatrix(100, 1);
    std::shared_ptr<Matrix> weights = Matrix::CreateMatrix(10, 100);
    std::shared_ptr<Matrix> biases = Matrix::CreateMatrix(10, 1);
    std::shared_ptr<Matrix> output = Matrix::C_EmptyProductMatrix(*weights.get(), *inputs.get());
    std::shared_ptr<Matrix> output2 = Matrix::C_EmptyProductMatrix(*weights.get(), *inputs.get());
    NMath::InitializeWeights(EInitialization::Random, EDistribution::Normal, *weights.get());
    Matrix::Product(*weights.get(), *inputs.get(), *output.get());
    Matrix::Add(*output.get(), *biases.get(), *output2.get());
    std::cout << "AA" << std::endl;

}