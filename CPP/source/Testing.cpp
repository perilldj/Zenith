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