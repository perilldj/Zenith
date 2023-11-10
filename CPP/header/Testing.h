#pragma once

#include "../header/NMath.h"
#include "../header/Network.h"

class Testing {

public:

    static bool RunTest();
    static void MatricesTest();

    static bool ActivationTest();
    static bool ActivationDerivativeTest();
    static bool MatrixTest();

    static bool SigmoidTest();
    static bool TanhTest();
    static bool ReLUTest();
    static bool LeakyReLUTest();
    static bool SiLUTest();
    static bool SoftplusTest();
    static bool SoftmaxTest();

    static bool dSigmoidTest();
    static bool dTanhTest();
    static bool dReLUTest();
    static bool dLeakyReLUTest();
    static bool dSiLUTest();
    static bool dSoftplusTest();
    static bool dSoftmaxTest();

    static bool ConstructionTest();
    static bool EqualSizeTest();
    static bool DimensionTest();
    static bool GetSetTest();
    static bool AddDataTest();
    static bool EqualsTest();
    static bool EmptyTest();
    static bool FillTest();
    static bool ClearTest();
    static bool MinimumMaximumTest();
    static bool ScaleTest();
    static bool ElementWiseArithmeticTest();
    static bool TransposeTest();
    static bool ProductTest();

};