#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

enum EDimension {
    NULL_DIMENSIONAL,
    ONE_DIMENSIONAL,
    TWO_DIMENSIONAL,
    THREE_DIMENSIONAL
};

class Matrix {

public:

    Matrix(int row_, bool isHorizontalVector_);
    Matrix(int row_, int col_);
    Matrix(int row_, int col_, int depth_);

    static std::shared_ptr<Matrix> CreateMatrix(int row, bool isHorizontalVector);
    static std::shared_ptr<Matrix> CreateMatrix(int row, int col);
    static std::shared_ptr<Matrix> CreateMatrix(int row, int col, int depth);

    float Get(int index);
    float Get(int row, int col);
    float Get(int row, int col, int depth);

    void Set(int index, float value);
    void Set(int row, int col, float value);
    void Set(int row, int col, int depth, float value);

    bool Empty();

    void Fill(float val);
    void Clear();
    float MaxElement();
    float MinElement();

    inline int GetRow() { return row; }
    inline int GetCol() { return col; }
    inline int GetDepth() { return depth; }

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

    bool CheckDimension(EDimension targetDimension);
    //void ResizeVector(int row, int col); ???

    std::vector<std::vector<std::vector<float>>> arr;
    EDimension matrixDimension = EDimension::NULL_DIMENSIONAL;
    bool isHorizontalVector = false;
    int row = 0;
    int col = 0;
    int depth = 0;

};