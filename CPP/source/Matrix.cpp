#include "../header/Matrix.h"

/*
    Matrix::Matrix(int row_, int col_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes the internal two-dimensional vector.
*/

Matrix::Matrix(int row_, int col_) :
    row(row_), col(col_) {
    arr.resize(row);
    for(int i = 0; i < row; i++)
        arr[i].resize(col);
}

/*
    std::shared_tr<Matrix> Matrix::CreateMatrix(int row, int col)
    Description: Creates a matrix with the specified matrix row and col size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int col) {
    return std::make_shared<Matrix>(row, col);
}

/*
    float Matrix::Get(int row, int col)
    Description: Returns the value at the specified row and col locations.
*/

float Matrix::Get(int row, int col) {
    if(row >= 0 && row < this->row && col >= 0 && col < this->col )
        return arr[row][col];
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;
}

/*
    void Matrix::Set(int row, int col, float value)
    Description: Sets the value at the specified row and col locations to the new provided value.
*/

void Matrix::Set(int row, int col, float value) {
    if(row >= 0 && row < this->row && col >= 0 && col < this->col ) {
        arr[row][col] = value;
        return;
    }     
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl; 
}

/*
    void Matrix::Fill(float val)
    Description: Fills the matrix with a specific value.
*/

void Matrix::Fill(float val) {
    for(int i = 0; i < row; i++)
        std::fill(arr[i].begin(), arr[i].end(), val);
}

/*
    void Matrix::Clear()
    Description: Sets the contents of the matrix to 0.
*/

void Matrix::Clear() {
    for(int i = 0; i < row; i++)
        std::fill(arr[i].begin(), arr[i].end(), 0.0f);
}

/*
    float Matrix::MaxElement();
    Description: Returns the largest value in the matrix.
*/

float Matrix::MaxElement() {
    float max = Get(0, 0);
    for(int i = 0; i < GetRow(); i++)
        for(int j = 0; j < GetCol(); j++)
            if(Get(i, j) > max)
                max = Get(i, j);
    return max;
}

/*
    float Matrix::MinElement();
    Description: Returns the lowest value in the matrix.
*/

float Matrix::MinElement() {
    float min = Get(0, 0);
    for(int i = 0; i < GetRow(); i++)
        for(int j = 0; j < GetCol(); j++)
            if(Get(i, j) < min)
                min = Get(i, j);
    return min;
}

/*
    void Matrix::Scale(float s, Matrix &mat)
    Description: Scales the provided matrix by the a scalar.
*/

void Matrix::Scale(float s, Matrix &mat) {
    for(int i = 0; i < mat.row; i++)
        for(int j = 0; j < mat.col; j++)
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
    for(int i = 0; i < mat.row; i++)
        for(int j = 0; j < mat.col; j++)
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
    for(int i = 0; i < mat1.row; i++)
        for(int j = 0; j < mat1.col; j++)
            out.Set(i, j, mat1.Get(i, j) + mat2.Get(i, j));
}

/*
    std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat)
    Description: Creates the transpose of the provided matrix.
*/

std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat) {
    std::shared_ptr<Matrix> out = std::make_shared<Matrix>(mat.col, mat.row);
    for(int i = 0; i < mat.row; i++)
        for(int j = 0; j < mat.col; j++)
            out->Set(i, j, mat.Get(j, i));
    return out;
}

/*
    void Matrix::Transpose(MAtrix &mat, Matrix &out)
    Description: Transposes a matrix to an alreaty initialized matrix.
                 The out matrix must be the correct size.
*/

void Matrix::Transpose(Matrix &mat, Matrix &out) {
    if(mat.row != out.col || mat.col != out.row)
        return;
    for(int i = 0; i < mat.row; i++)
        for(int j = 0; j < mat.col; j++)
            out.Set(i, j, mat.Get(j, i));
}

/*
    std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2)
    Description: Creates a matrix that is the size of what the resulting size form the product
                 of the two provided matrices would be.
*/

std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2) {
    if(mat1.col != mat2.row) {
        std::cout << "Matrix.cpp - [ERROR] - Empty product matrix creation imposible with given matrices" << std::endl;
        return std::shared_ptr<Matrix>();
    }
    return std::make_shared<Matrix>(mat1.row, mat2.col);
}

/*
    void Matrix::Product(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Performs matrix multiplication and stores the result in the out matrix
                 passed by reference.
*/

void Matrix::Product(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(mat1.col != mat2.row) {
        std::cout << "Matrix.cpp - [ERROR] - Matrix multiplication imposible with given matrices" << std::endl;
        return;
    }
    float result = 0.0f;
    for(int i = 0; i < mat1.row; i++) {
        for(int j = 0; j < mat2.col; j++) {
            for(int k = 0; k < mat1.row; k++) {
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
    return (mat1.row == mat2.row && mat1.col == mat2.col);
}