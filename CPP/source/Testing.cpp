#include "../header/Testing.h"

void Testing::RunTest() {
    
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

    std::cout << "done" << std::endl;

}