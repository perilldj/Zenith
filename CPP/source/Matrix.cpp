#include "../header/Matrix.h"

/*
    Matrix::Matrix(int col_, int row_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes the internal two-dimensional vector.
*/

Matrix::Matrix(int col_, int row_) :
    col(col_), row(row_) {
    arr.resize(col);
    for(int i = 0; i < col; i++)
        arr[i].resize(row);
}

/*
    std::shared_tr<Matrix> Matrix::CreateMatrix(int col, int row)
    Description: Creates a matrix with the specified matrix column and row size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int col, int row) {
    return std::make_shared<Matrix>(col, row);
}

/*
    float Matrix::Get(int col, int row)
    Description: Returns the value at the specified column and row locations.
*/

float Matrix::Get(int col, int row) {
    if(col >= 0 && col < this->col && row >= 0 && row < this->row )
        return arr[col][row];
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;
}

/*
    void Matrix::Set(int col, int row, float value)
    Description: Sets the value at the specified column and row locations to the new provided value.
*/

void Matrix::Set(int col, int row, float value) {
    if(col >= 0 && col < this->col && row >= 0 && row < this->row ) {
        arr[col][row] = value;
        return;
    }     
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl; 
}

void Matrix::Fill(float val) {
    for(int i = 0; i < col; i++)
        std::fill(arr[i].begin(), arr[i].end(), val);
}

/*
    void Matrix::Scale(float s, Matrix &mat)
    Description: Scales the provided matrix by the a scalar.
*/

void Matrix::Scale(float s, Matrix &mat) {
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            mat.arr[i][j] *= s;
}

/*
    void Matrix::Scale(float s, Matrix &mat, Matrix &out)
    Description: Scales the provided matrix by a scalar, but stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Scale(float s, Matrix &mat, Matrix &out) {
    if(!IsEqualSize(mat, out))
        return;
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            out.Set(i, j, mat.Get(i, j) * s);
}

/*
    void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Adds two same size matrices together, stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out))
        return;
    for(int i = 0; i < mat1.col; i++)
        for(int j = 0; j < mat1.row; j++)
            out.Set(i, j, mat1.Get(i, j) + mat2.Get(i, j));
}

/*
    void Matrix::Transpose(MAtrix &mat, Matrix &out)
    Description: Transposes a matrix to an alreaty initialized matrix.
                 The out matrix must be the correct size.
*/

void Matrix::Transpose(Matrix &mat, Matrix &out) {
    if(mat.col != out.row || mat.row != out.col)
        return;
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            out.Set(i, j, mat.Get(j, i));
}

/*
    std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat)
    Description: Creates the transpose of the provided matrix.
*/

std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat) {
    std::shared_ptr<Matrix> out = std::make_shared<Matrix>(mat.row, mat.col);
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            out->Set(i, j, mat.Get(j, i));
    return out;
}

/*
    std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2)
    Description: Creates a matrix that is the size of what the resulting size form the product
                 of the two provided matrices would be.
*/

std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2) {
    if(mat1.row != mat2.col) {
        std::cout << "Matrix.cpp - [ERROR] - Empty product matrix creation imposible with given matrices" << std::endl;
        return std::shared_ptr<Matrix>();
    }
    return std::make_shared<Matrix>(mat1.col, mat2.row);
}

/*
    void Matrix::Product(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Performs matrix multiplication and stores the result in the out matrix
                 passed by reference.
*/

void Matrix::Product(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(mat1.row != mat2.col) {
        std::cout << "Matrix.cpp - [ERROR] - Matrix multiplication imposible with given matrices" << std::endl;
        return;
    }
    float result = 0.0f;
    for(int i = 0; i < mat1.row; i++) {
        for(int j = 0; j < mat2.col; j++) {
            for(int k = 0; k < mat1.col; j++) {
                result += mat1.Get(i, k) * mat2.Get(k, j);
            }
            out.Set(i, j, result);
            result = 0.0f;
        }
    }

}

/*
    bool Matrix::IsEqualSize(MAtrix &mat1, Matrix &mat2)
    Description: Checks if the two provided matrixes are the same size.
*/

bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2) {
    return (mat1.col == mat2.col && mat1.row == mat2.row);
}