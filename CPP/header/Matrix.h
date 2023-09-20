#pragma once
#include <vector>
#include <iostream>

class Matrix {

public:

    Matrix(int col_, int row_);
    float Get(int col, int row);
    void Set(int col, int row, float value);

    static void Scale(float s, Matrix &mat);
    static void Scale(float s, Matrix &mat, Matrix &out);

    static void Add(Matrix &mat1, Matrix &mat2, Matrix &out);

    //static void Transpose(Matrix &mat, Matrix &out);

private:

    static bool IsEqualSize(Matrix &mat1, Matrix &mat2);

    std::vector<std::vector<float>> arr;
    int col = 0;
    int row = 0;

};