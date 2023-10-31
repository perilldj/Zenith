#include "../header/Testing.h"

bool Testing::RunTest() {
    bool isTestSuccessful = true;
    std::cout << "[EXEC] - Running Full Test" << std::endl;
    bool result = ( ActivationTest()            & 
                    ActivationDerivativeTest()    );
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Full Test" << std::endl;       
    return isTestSuccessful;
}

bool Testing::ActivationTest() {
    std::cout << "[EXEC] - Running Activation Function Test" << std::endl;
    bool result = ( SigmoidTest()   &
                    TanhTest()      &
                    ReLUTest()      &
                    LeakyReLUTest() &
                    SiLUTest()      &
                    SoftplusTest()  &
                    SoftmaxTest()     );
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Activation Function Test" << std::endl;
    return result;
}

bool Testing::SigmoidTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.5f, 0.6224593f, 0.7310586f, 0.9999546f, 
                                    0.3775407f, 0.2689414f, 0.0000454f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::Sigmoid, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Sigmoid" << std::endl;
    return result;
}

bool Testing::TanhTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.0f, 0.462117, 0.761594, 0.999999f, 
                                    -0.462117, -0.761594, -0.999999f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::Tanh, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Tanh" << std::endl;
    return result;
}

bool Testing::ReLUTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.0f, 0.5f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::ReLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - ReLU" << std::endl;
    return result;
}

bool Testing::LeakyReLUTest(){
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.0f, 0.5f, 1.0f, 10.0f, 
                                    -0.005f, -0.01f, -0.1f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::LeakyReLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Leaky ReLU" << std::endl;
    return result;
}

bool Testing::SiLUTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.0f, 0.3112296f, 0.7310586f, 9.999546f, 
                                    -0.18877035f, -0.2689414f, 0.0000454f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::SiLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - SiLU" << std::endl;
    return result;
}

bool Testing::SoftplusTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.69314f, 0.97407f, 1.31326f, 10.00004f, 
                                    0.47407f, 0.313261f, 0.0000454f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::Softplus, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Softplus" << std::endl;
    return result;
}

bool Testing::SoftmaxTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 2.0f, -0.7f, -1.0f, -0.1f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.06884f, 0.1135f, 0.1871f, 0.50867f, 
                                    0.03418f, 0.025325f, 0.06229f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::Activation(EActivation::Softmax, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Softmax" << std::endl;
    return result;
}

bool Testing::ActivationDerivativeTest() {
    std::cout << "[EXEC] - Running Activation Function Derivative Test" << std::endl;
    bool result = ( dSigmoidTest()   &
                    dTanhTest()      &
                    dReLUTest()      &
                    dLeakyReLUTest() &
                    dSiLUTest()      &
                    dSoftplusTest()  &
                    dSoftmaxTest()     );
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Activation Function Derivative Test" << std::endl;
    return result;
}

bool Testing::dSigmoidTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.25f, 0.235003f, 0.196611f, 0.0000454f, 
                                    0.235003f, 0.196611f, 0.0000454f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::Sigmoid, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Sigmoid Derivative" << std::endl;
    return result;
}

bool Testing::dTanhTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 1.0f, 0.78644f, 0.419974f, 0.0f, 
                                    0.78644f, 0.419974f, 0.0f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::Tanh, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Tanh Derivative" << std::endl;
    return result;
}

bool Testing::dReLUTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::ReLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - ReLU Derivative" << std::endl;
    return result;
}

bool Testing::dLeakyReLUTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.01f, 1.0f, 1.0f, 1.0f, 0.01f, 0.01f, 0.01f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::LeakyReLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Leaky ReLU Derivative" << std::endl;
    return result;
}

bool Testing::dSiLUTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.5f, 0.73996f, 0.92767f, 1.0f, 0.26003f, 0.07232f, -0.0004f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::SiLU, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - SiLU Derivative" << std::endl;
    return result;
}

bool Testing::dSoftplusTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.5f, 0.6224593f, 0.7310586f, 0.9999546f, 
                                    0.3775407f, 0.2689414f, 0.0000454f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::Softplus, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Softplus Derivative" << std::endl;
    return result;
}

bool Testing::dSoftmaxTest() {
    bool result = true;
    std::vector<float> inputs   = { 0.0f, 0.5f, 1.0f, 2.0f, -0.7f, -1.0f, -0.1f };
    std::shared_ptr<Matrix> mInputs = Matrix::CreateMatrix(inputs.size(), false);
    mInputs->AddData(inputs);
    std::vector<float> expected = { 0.064105f, 0.10062f, 0.15211f, 0.24992f, 
                                    0.033018f, 0.024685f, 0.058413f };
    std::shared_ptr<Matrix> mExpected = Matrix::CreateMatrix(expected.size(), false);
    std::shared_ptr<Matrix> mActual = Matrix::CreateMatrix(*mInputs.get(), false);
    mExpected->AddData(expected);
    NMath::ActivationGradient(EActivation::Softmax, *mInputs.get(), *mActual.get());
    result = Matrix::EqualsWithinMargin(*mActual.get(), *mExpected.get(), 0.01f);
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Softmax Derivative" << std::endl;
    return result;
}

void Testing::MatrixTest() {

    Matrix mat10x1 = Matrix(10, false);
    Matrix mat1x10 = Matrix(10, true);
    Matrix mat2D = Matrix(10, 10);
    Matrix mat3D = Matrix(10, 9, 8);
    std::cout << mat10x1 << " " << mat1x10
              << mat2D << " " << mat3D << std::endl;

    std::cout << mat10x1.Get(5) << std::endl;
    mat10x1.Set(5, 5);
    std::cout << mat10x1.Get(5) << std::endl;

    std::cout << mat1x10.Get(5) << std::endl;
    mat1x10.Set(5, 6);
    std::cout << mat1x10.Get(5) << std::endl;

    std::cout << mat2D.Get(9, 5) << std::endl;
    mat2D.Set(9, 5, 10);
    std::cout << mat2D.Get(9, 5) << std::endl;
    
    std::cout << mat3D.Get(9, 5, 7) << std::endl;
    mat3D.Set(9, 5, 7, 15);
    std::cout << mat3D.Get(9, 5, 7) << std::endl;

    Matrix empty = Matrix(0, false);
    if(empty.Empty())
        std::cout << "Matrix is empty" << std::endl;
    else
        std::cout << "Matrix is not empty" << std::endl;

    if(mat3D.Empty())
        std::cout << "Matrix is empty" << std::endl;
    else
        std::cout << "Matrix is not empty" << std::endl;

    std::cout << mat3D.GetDepth() << " " << mat3D.GetRow() 
              << " " << mat3D.GetCol() << std::endl;

    Matrix f = Matrix(10, 10, 10);
    f.Fill(10.0f);
    std::cout << f.Get(5, 5, 5) << " " << f.Get(0, 0, 0) 
              << " " << f.Get(9, 9, 9) << std::endl;
    f.Clear();
    std::cout << f.Get(5, 5, 5) << " " << f.Get(0, 0, 0) 
              << " " << f.Get(9, 9, 9) << std::endl;

    f.Set(5, 4, 5, 10.1f);
    f.Set(2, 7, 3, -5.0f);
    f.Set(1, 1, 2, 4.5f);
    std::cout << f.MaxElement() << " " << f.MinElement() << std::endl;

    f.Scale(2.0f);
    std::cout << f.MaxElement() << " " << f.MinElement() << std::endl;
    std::shared_ptr<Matrix> g = Matrix::CreateMatrix(f, false);
    Matrix::Scale(2.0f, f, *g.get());
    std::cout << f.MaxElement() << " " << f.MinElement() << std::endl;
    std::cout << g->MaxElement() << " " << g->MinElement() << std::endl;

    Matrix m1 = Matrix(3, 3);
    Matrix m2 = Matrix(3, 3);
    m1.Fill(1.0f);
    m2.Fill(2.0f);
    m1.Set(2, 2, 3.0f);
    std::shared_ptr<Matrix> m3 = Matrix::CreateMatrix(m1, false);
    Matrix::Add(m1, m2, *m3.get());
    std::cout << m3->Get(2, 2) << " " << m3->Get(0, 0) << std::endl;

    m1.Fill(1.0f);
    m2.Fill(2.0f);
    m1.Set(2, 2, 3.0f);
    Matrix::Subtract(m1, m2, *m3.get());
    std::cout << m3->Get(2, 2) << " " << m3->Get(0, 0) << std::endl;

    m1.Fill(2.0f);
    m1.Set(2, 2, 3.0f);
    Matrix::ElementWiseMultiplication(m1, m2, *m3.get());
    std::cout << m3->Get(2, 2) << " " << m3->Get(0, 0) << std::endl;

    std::cout << mat10x1 << std::endl;
    std::shared_ptr<Matrix> t = Matrix::C_Transpose(mat10x1);
    std::cout << *t.get() << std::endl;

    m1.Fill(1.0f);
    m1.Set(2, 0, 2.0f);
    m1.Set(0, 2, 3.0f);
    std::cout << m1.Get(2, 0) << " " << m1.Get(0, 2) << std::endl;
    Matrix t1 = Matrix(3, 3);
    Matrix::Transpose(m1, t1);
    std::cout << t1.Get(2, 0) << " " << t1.Get(0, 2) << std::endl;

    mat1x10.Fill(2.0f);
    mat10x1.Fill(3.0f);
    std::shared_ptr<Matrix> product = Matrix::C_EmptyProductMatrix(mat10x1, mat1x10);
    Matrix::Product(mat10x1, mat1x10, *product.get());
    std::cout << *product.get() << std::endl;
    std::cout << product->Get(0, 0) << " " << product->Get(9, 9) << std::endl;


    std::cout << "done" << std::endl;

}