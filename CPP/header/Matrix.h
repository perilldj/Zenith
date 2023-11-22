#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

#include <pybind11/numpy.h>
namespace py = pybind11;

enum EDimension {
    NULL_DIMENSIONAL,
    ONE_DIMENSIONAL,
    TWO_DIMENSIONAL,
    THREE_DIMENSIONAL
};

class Matrix {

public:

    static const bool STANDARD_CONVOLUTION = false;
    static const bool FULL_CONVOLUTION = true;

public:

    Matrix(int length, bool isHorizontalVector_);
    Matrix(int row_, int col_);
    Matrix(int depth_, int row_, int col_);

    static std::shared_ptr<Matrix> CreateMatrix(Matrix &m, bool copyElements);
    static std::shared_ptr<Matrix> CreateMatrix(int length, bool isHorizontalVector);
    static std::shared_ptr<Matrix> CreateMatrix(int row, int col);
    static std::shared_ptr<Matrix> CreateMatrix(int depth, int row, int col);

    int AddData(py::array_t<float> &data);
    int AddData(std::vector<float> &data);
    static void CopyData(Matrix &copy, Matrix &out);

    float Get(int index);
    float Get(int row, int col);
    float Get(int depth, int row, int col);

    void Set(int index, float value);
    void Set(int row, int col, float value);
    void Set(int depth, int row, int col, float value);

    bool Empty();
    bool IsLocationInBounds(int d, int r, int c);

    void Fill(float val);
    void Clear();
    float MaxElement();
    float MaxElement(int &d, int &r, int &c);
    float MinElement();

    inline int GetDepth() const { return depth; }
    inline int GetRow() const { return row; }
    inline int GetCol() const { return col; }

    EDimension GetDimension();

    void Scale(float s);
    static void Scale(float s, Matrix &mat, Matrix &out);

    static bool Equals(Matrix &mat1, Matrix &mat2);
    static bool EqualsWithinMargin(Matrix &mat1, Matrix &mat2, float delta);
    
    static void Add(Matrix &mat1, Matrix &mat2, Matrix &out);
    static void Subtract(Matrix &mat1, Matrix &mat2, Matrix &out);
    static void ElementWiseMultiplication(Matrix &mat1, Matrix &mat2, Matrix &out);

    static std::shared_ptr<Matrix> C_Transpose(Matrix &mat);
    static void Transpose(Matrix &mat, Matrix &out);

    static std::shared_ptr<Matrix> C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2);
    static void Product(Matrix &mat1, Matrix &mat2, Matrix &out);
    static void AccumulateProduct(Matrix &mat1, Matrix &mat2, Matrix &out);

    static std::shared_ptr<Matrix> C_EmptyConvolutionMatrix(bool convolutionType, Matrix &in, Matrix &kernels);
    static void Convolution(bool convolutionType, Matrix &in, Matrix &kernel, Matrix &out, int outputChannel);

    static bool IsEqualSize(Matrix &mat1, Matrix &mat2);

private:

    static float ConvolveIndex(int rowIndex, int colIndex, Matrix &in, Matrix &kernel);
    bool CheckDimension(EDimension targetDimension);
    //void ResizeVector(int row, int col); ???

    std::vector<std::vector<std::vector<float>>> arr;
    EDimension matrixDimension = EDimension::NULL_DIMENSIONAL;
    bool isHorizontalVector = false;
    int depth = 0;
    int row = 0;
    int col = 0;

};

std::ostream &operator<<(std::ostream &os, const Matrix &m);