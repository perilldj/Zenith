#include "../header/Testing.h"

void Testing::RunTest() {
    
    auto mat = Matrix::CreateMatrix(10, 10);
    int val = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            mat->Set(i, j, val);
            val++;
        }
    }

    auto mat2 = Matrix::C_Transpose(*mat.get());
    std::cout << "A" << std::endl;

}