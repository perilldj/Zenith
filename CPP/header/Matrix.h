#pragma once
#include <vector>
#include <iostream>
#include <memory>

class Matrix {

public:

    Matrix(int col_, int row_);

    static std::shared_ptr<Matrix> CreateMatrix(int col, int row);

    float Get(int col, int row);
    void Set(int col, int row, float value);

    void Fill(float val);

    static void Scale(float s, Matrix &mat);
    static void Scale(float s, Matrix &mat, Matrix &out);

    static void Add(Matrix &mat1, Matrix &mat2, Matrix &out);

    static void Transpose(Matrix &mat, Matrix &out);
    static std::shared_ptr<Matrix> C_Transpose(Matrix &mat);

    static std::shared_ptr<Matrix> C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2);
    static void Product(Matrix &mat1, Matrix &mat2, Matrix &out);

private:

    static bool IsEqualSize(Matrix &mat1, Matrix &mat2);

    std::vector<std::vector<float>> arr;
    int col = 0;
    int row = 0;

};