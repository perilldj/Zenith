#pragma once

#include "../header/NMath.h"
#include "../header/Network.h"

class Testing {

public:

    static bool RunTest();
    static void MatrixTest();

    static bool ActivationTest();
    static bool ActivationDerivativeTest();

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

};