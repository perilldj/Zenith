#include "../header/Matrix.h"

Matrix::Matrix(int col_, int row_) :
    col(col_), row(row_) {
    arr.resize(col);
    for(int i = 0; i < col; i++)
        arr[i].resize(row);
}

float Matrix::Get(int col, int row) {
    if(col >= 0 && col < this->col && row >= 0 && row < this->row )
        return arr[col][row];
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;
}

void Matrix::Set(int col, int row, float value) {
    if(col >= 0 && col < this->col && row >= 0 && row < this->row ) {
        arr[col][row] = value;
        return;
    }     
    std::cerr << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl; 
}

void Matrix::Scale(float s, Matrix &mat) {
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            mat.arr[i][j] *= s;
}

void Matrix::Scale(float s, Matrix &mat, Matrix &out) {
    if(!IsEqualSize(mat, out))
        return;
    for(int i = 0; i < mat.col; i++)
        for(int j = 0; j < mat.row; j++)
            out.Set(i, j, mat.Get(i, j) * s);
}

void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out))
        return;
    for(int i = 0; i < mat1.col; i++)
        for(int j = 0; j < mat1.row; j++)
            out.Set(i, j, mat1.Get(i, j) + mat2.Get(i, j));
}

bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2) {
    return (mat1.col == mat2.col && mat1.row == mat2.row);
}