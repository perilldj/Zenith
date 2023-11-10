#include "../header/Testing.h"

bool Testing::RunTest() {
    bool isTestSuccessful = true;
    std::cout << "[EXEC] - Running Full Test" << std::endl;
    bool result = ( ActivationTest()            & 
                    ActivationDerivativeTest()  &
                    MatrixTest()                  );
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
    std::vector<float> inputs = { 0.0f, 0.5f, 1.0f, 10.0f, -0.5f, -1.0f, -10.0f };
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

bool Testing::MatrixTest() {
    std::cout << "[EXEC] - Running Matrix Test" << std::endl;
    bool result = ( ConstructionTest()          &
                    EqualSizeTest()             &   
                    DimensionTest()             &
                    GetSetTest()                &
                    AddDataTest()               &
                    EqualsTest()                &
                    EmptyTest()                 &
                    FillTest()                  &
                    ClearTest()                 &
                    MinimumMaximumTest()        &       
                    ScaleTest()                 &
                    ElementWiseArithmeticTest() &
                    TransposeTest()             &
                    ProductTest()                 );
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Matrix Test" << std::endl;       
    return result;
}

bool Testing::ConstructionTest() {
    bool result = true;
    int size1 = 10, size2 = 5, size3 = 3;
    Matrix m1 = Matrix(size1, false);
    Matrix m2 = Matrix(size1, true);
    if(m1.GetCol() != m2.GetRow() || m1.GetRow() != m2.GetCol())
        result = false;
    if(m1.GetRow() != size1 || m2.GetCol() != size1)
        result = false;
    Matrix m3 = Matrix(size1, size2);
    if(m3.GetRow() != size1 || m3.GetCol() != size2)
        result = false;
    Matrix m4 = Matrix(size1, size2, size3);
    if(m4.GetDepth() != size1 || m4.GetRow() != size2 || m4.GetCol() != size3)
        result = false;
    auto m5 = Matrix::CreateMatrix(m4, false);
    if(m5->GetDepth() != size1 || m5->GetRow() != size2 || m5->GetCol() != size3)
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Construction" << std::endl;
    return result;
}

bool Testing::EqualSizeTest() {
    bool result = false;
    int size1 = 10, size2 = 5, size3 = 3;
    Matrix m1 = Matrix(size1, size2, size3);
    Matrix m2 = Matrix(size3, size2, size1);
    Matrix m3 = Matrix(size1, size2, size3);
    if(!Matrix::IsEqualSize(m1, m2) && Matrix::IsEqualSize(m1, m3))
        result = true;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Equal Size" << std::endl;
    return result;
}

bool Testing::DimensionTest() {
    bool result = true;
    int size1 = 10, size2 = 5, size3 = 3;
    Matrix m1 = Matrix(size2, false);
    Matrix m2 = Matrix(size2, size3);
    Matrix m3 = Matrix(size1, size2, size3);
    if(m1.GetDimension() != EDimension::ONE_DIMENSIONAL)
        result = false;
    if(m2.GetDimension() != EDimension::TWO_DIMENSIONAL)
        result = false;
    if(m3.GetDimension() != EDimension::THREE_DIMENSIONAL)
        result = false;
    Matrix m4 = Matrix(1, size1);
    if(m4.GetDimension() != EDimension::ONE_DIMENSIONAL)
        result = false;
    Matrix m5 = Matrix(1, size1, 1);
    if(m5.GetDimension() != EDimension::ONE_DIMENSIONAL)
        result = false;
    Matrix m6 = Matrix(1, size1, size2);
    if(m6.GetDimension() != EDimension::TWO_DIMENSIONAL)
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Dimension" << std::endl;
    return result;
}

bool Testing::GetSetTest() {
    bool result = true;
    int size1 = 10, size2 = 5, size3 = 3;
    Matrix m1 = Matrix(size2, false);
    Matrix m2 = Matrix(size2, size3);
    Matrix m3 = Matrix(size1, size2, size3);
    float before = 0.0f, target = 5.0f, after = 0.0f;
    before = m1.Get(1); after = m1.Get(1);
    m1.Set(1, target);
    after = m1.Get(1);
    if(before == after || after != target)
        result = false;
    before = m2.Get(1, 1); after = m2.Get(1, 1);
    m2.Set(1, 1, target);
    after = m2.Get(1, 1);
    if(before == after || after != target)
        result = false;
    before = m3.Get(1, 1, 1); after = m3.Get(1, 1, 1);
    m3.Set(1, 1, 1, target);
    after = m3.Get(1, 1, 1);
    if(before == after || after != target)
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Get Set" << std::endl;        
    return result;
}

bool Testing::AddDataTest() {

    bool result = true;

    std::vector<float> data = {
                                    1.0f,  2.0f,  3.0f,  4.0f,  5.0f,
                                    6.0f,  7.0f,  8.0f,  9.0f,  10.0f,
                                    11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                    16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                    21.0f, 22.0f, 23.0f, 24.0f, 25.0f
                              };
                              
    Matrix m1 = Matrix(5, 5);
    m1.AddData(data);
    for(int i = 0; i < m1.GetRow(); i++)
        for(int j = 0; j < m1.GetRow(); j++)
            if(m1.Get(i, j) != data[i * 5 + j])
                result = false;

    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Add Data" << std::endl;
    return result;

}

bool Testing::EqualsTest() {
    bool result = true;
    Matrix m1 = Matrix(2, 5, 3);
    Matrix m2 = Matrix(2, 5, 3);
    m1.Fill(1.0f);
    m2.Fill(1.0f);
    if(!Matrix::Equals(m1, m2))
        result = false;
    m2.Fill(1.1f);
    if(Matrix::Equals(m1, m2))
        result = false;
    if(Matrix::EqualsWithinMargin(m1, m2, 0.01f))
        result = false;
    if(!Matrix::EqualsWithinMargin(m1, m2, 0.2f))
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Equals" << std::endl;
    return result;
}

bool Testing::EmptyTest() {
    return true; // unused
}

bool Testing::FillTest() {
    bool result = false;
    Matrix m1 = Matrix(2, 5, 3);
    m1.Fill(1.0f);
    if(m1.Get(1, 2, 1) == m1.Get(0, 0, 0) && m1.Get(0, 0, 0) == m1.Get(1, 4, 2))
        result = true;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Fill" << std::endl;
    return result;
}

bool Testing::ClearTest() {
    bool result = false;
    Matrix m1 = Matrix(2, 5, 3);
    m1.Fill(1.0f);
    m1.Clear();
    if(m1.Get(0, 0, 0) == 0.0f && m1.Get(1, 4, 2) == 0.0f)
        result = true;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Clear" << std::endl;
    return result;
}

bool Testing::MinimumMaximumTest() {
    bool result = true;
    Matrix m1 = Matrix(2, 5, 3);
    float val1 = -1.0f, val2 = 2.3f, val3 = 5.0f;
    m1.Set(0, 0, 0, val1);
    m1.Set(1, 2, 1, val2);
    m1.Set(1, 4, 2, val3);
    if(m1.MinElement() != val1)
        result = false;
    if(m1.MaxElement() != val3)
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Minimum Maximum" << std::endl;
    return result;
}

bool Testing::ScaleTest() {
    bool result = true;
    Matrix m1 = Matrix(2, 5, 3);
    m1.Fill(1.0f);
    m1.Scale(2.0f);
    if(m1.Get(0, 0, 0) != 2.0f || m1.Get(1, 4, 2) != 2.0f)
        result = false;
    m1.Scale(0.1f);
    if(m1.Get(0, 0, 0) != 0.2f || m1.Get(1, 4, 2) != 0.2f)
        result = false;
    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Scale" << std::endl;
    return result;
}

bool Testing::ElementWiseArithmeticTest() {

    bool result = true;

    Matrix out = Matrix(3, 3);

    std::vector<float> d1 = {
                                 0.0f, 1.0f,  0.5f,
                                -1.0f, 2.0f, -1.5f,
                                 3.0f, 0.1f, -0.1f
                            };

    std::vector<float> d2 = {
                                 1.0f,  2.0f, -0.5f,
                                 0.0f,  1.0f,  3.0f,
                                -0.1f,  2.0f, -1.0f
                            };

    Matrix m1 = Matrix(3, 3);
    Matrix m2 = Matrix(3, 3);

    m1.AddData(d1);
    m2.AddData(d2);

    std::vector<float> ad = {
                                 1.0f,  3.0f,  0.0f,
                                -1.0f,  3.0f,  1.5f,
                                 2.9f,  2.1f, -1.1f
                            };

    Matrix am = Matrix(3, 3);
    am.AddData(ad);

    Matrix::Add(m1, m2, out);
    if(!Matrix::EqualsWithinMargin(am, out, 0.01f))
        result = false;

    std::vector<float> sd = {
                                -1.0f, -1.0f,  1.0f,
                                -1.0f,  1.0f, -4.5f,
                                 3.1f, -1.9f,  0.9f
                            };

    Matrix sm = Matrix(3, 3);
    sm.AddData(sd);
    
    Matrix::Subtract(m1, m2, out);
    if(!Matrix::EqualsWithinMargin(sm, out, 0.01f))
        result = false;

    std::vector<float> md = {
                                 0.0f, 2.0f, -0.25f,
                                 0.0f, 2.0f, -4.5f,
                                -0.3f, 0.2f,  0.1f
                            };

    Matrix mm = Matrix(3, 3);
    mm.AddData(md);

    Matrix::ElementWiseMultiplication(m1, m2, out);
    if(!Matrix::EqualsWithinMargin(mm, out, 0.01f))
        result = false;

    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Element Wise Arithmetic" << std::endl;
    return result;

}

bool Testing::TransposeTest() {

    bool result = true;

    std::vector<float> d1 = {
                                -1.0f, 2.0f, -1.5f,
                                 3.0f, 0.1f, -0.1f
                            };

    Matrix m1 = Matrix(2, 3);
    m1.AddData(d1);

    std::vector<float> dExpected {
                                    -1.0f,  3.0f,
                                     2.0f,  0.1f,
                                    -1.5f, -0.1f
                                };

    Matrix expected = Matrix(3, 2);
    expected.AddData(dExpected);

    std::shared_ptr<Matrix> m2 = Matrix::C_Transpose(m1);

    if(!Matrix::EqualsWithinMargin(*m2.get(), expected, 0.01f))
        result = false;

    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Transpose" << std::endl;
    return result;

}

bool Testing::ProductTest() {

    bool result = true;

    std::vector<float> d1 = {
                                -1.0f, 2.0f, -1.5f,
                                 3.0f, 0.1f, -0.1f
                            };

    Matrix m1 = Matrix(2, 3);
    m1.AddData(d1);

    std::vector<float> d2 = {
                                -1.0f,  3.0f,
                                 2.0f,  0.1f,
                                -1.5f, -0.1f
                            };

    Matrix m2 = Matrix(3, 2);
    m2.AddData(d2);

    std::vector<float> dExpected {
                                     7.25f, -2.65f,
                                    -2.65f,  9.02f
                                 };

    Matrix expected = Matrix(2, 2);
    expected.AddData(dExpected);

    Matrix m3 = Matrix(2, 2);
    Matrix::Product(m1, m2, m3);

    if(!Matrix::EqualsWithinMargin(expected, m3, 0.01f))
        result = false;

    std::cout << '[' << ((result) ? "PASS" : "FAIL") << "] - Product" << std::endl;
    return result;

}

void Testing::MatricesTest() {

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