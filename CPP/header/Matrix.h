#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

class Matrix {

public:

    Matrix(int row_, int col_);

    static std::shared_ptr<Matrix> CreateMatrix(int row, int col);

    float Get(int row, int col);
    void Set(int row, int col, float value);

    bool Empty();

    void Fill(float val);
    void Clear();
    float MaxElement();
    float MinElement();

    inline float GetRow() { return row; }
    inline float GetCol() { return col; }

    static void Scale(float s, Matrix &mat);
    static void Scale(float s, Matrix &mat, Matrix &out);

    static void Add(Matrix &mat1, Matrix &mat2, Matrix &out);
    static void Subtract(Matrix &mat1, Matrix &mat2, Matrix &out);
    static void ElementWiseMultiplication(Matrix &mat1, Matrix &mat2, Matrix &out);

    static std::shared_ptr<Matrix> C_Transpose(Matrix &mat);
    static void Transpose(Matrix &mat, Matrix &out);

    static std::shared_ptr<Matrix> C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2);
    static void Product(Matrix &mat1, Matrix &mat2, Matrix &out);

    static bool IsEqualSize(Matrix &mat1, Matrix &mat2);

private:

    std::vector<std::vector<float>> arr;
    int row = 0;
    int col = 0;

};