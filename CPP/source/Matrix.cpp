#include "../header/Matrix.h"

/*
    Matrix::Matrix(int row_, bool isHorizontalVector_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int row_, bool isHorizontalVector_) :
    row(row_), isHorizontalVector(isHorizontalVector_) {
    arr.resize(1);
    matrixDimension = ONE_DIMENSIONAL;
    if(!isHorizontalVector) {
        arr[0].resize(row);
        for(int i = 0; i < row; i++)
            arr[0][i].resize(1);
    } else {
        arr[0].resize(1);
        arr[0][0].resize(row);
    }
}

/*
    Matrix::Matrix(int row_, int col_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int row_, int col_) :
    row(row_), col(col_) {
    matrixDimension = TWO_DIMENSIONAL;
    arr.resize(1);
    arr[0].resize(row);
    for(int i = 0; i < row; i++)
        arr[0][i].resize(col);
}

/*
    Matrix::Matrix(int row_, int col_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int row_, int col_, int depth_) :
    row(row_), col(col_), depth(depth_) {
    arr.resize(depth);
    matrixDimension = THREE_DIMENSIONAL;
    for(int i = 0; i < depth; i++) {
        arr[i].resize(row);
        for(int j = 0; j < depth; j++)
            arr[i][j].resize(col);
    }
}

/*
    std::shared_tr<Matrix> Matrix::CreateMatrix(int row, int isHorizontalVector)
    Description: Creates a matrix with the specified matrix row and orientation.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, bool isHorizontalVector) {
    return std::make_shared<Matrix>(row, isHorizontalVector);
}


/*
    std::shared_tr<Matrix> Matrix::CreateMatrix(int row, int col)
    Description: Creates a matrix with the specified matrix row and col size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int col) {
    return std::make_shared<Matrix>(row, col);
}

/*
    std::shared_tr<Matrix> Matrix::CreateMatrix(int row, int col, int depth)
    Description: Creates a matrix with the specified matrix row, col, and depth size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int col, int depth) {
    return std::make_shared<Matrix>(row, col, depth);
}

/*
    float Matrix::Get(int index)
    Description: Returns the value from a vector at the specified index.
*/

float Matrix::Get(int index) {
    
    if(!CheckDimension(ONE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Get(int index) function accepts 1-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return 0.0f;
    }

    if(!isHorizontalVector) {
        if(index >= 0 && index < col)
            return arr[0][0][index];
    } else {
        if(index >= 0 && index < row)
            return arr[0][index][0];
    }

    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;

}

/*
    float Matrix::Get(int row, int col)
    Description: Returns the value at the specified row and col locations.
*/

float Matrix::Get(int row, int col) {

    if(!CheckDimension(TWO_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Get(int index) function accepts 2-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return 0.0f;
    }

    if(row >= 0 && row < this->row && col >= 0 && col < this->col )
        return arr[0][row][col];
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;

}

/*
    float Matrix::Get(int row, int col)
    Description: Returns the value at the specified row, col, and depth locations.
*/

float Matrix::Get(int row, int col, int depth) {

    if(!CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Get(int row, int col) function accepts 3-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return 0.0f;
    }

    if(row >= 0 && row < this->row && col >= 0 && col < this->col && depth >= 0 && depth < this->depth)
        return arr[depth][row][col];
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;

}

/*
    void Matrix::Set(int index, float value)
    Description: Sets the value at the specified index location to the new provided value.
*/

void Matrix::Set(int index, float value) {

    if(!CheckDimension(ONE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Set(int index, float value) function accepts 1-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return;
    }

    if(!isHorizontalVector) {
        if(index >= 0 && index < col)
            arr[0][0][index] = value;
    } else {
        if(index >= 0 && index < row)
            arr[0][index][0] = value;
    }

    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return;

}

/*
    void Matrix::Set(int row, int col, float value)
    Description: Sets the value at the specified row and col locations to the new provided value.
*/

void Matrix::Set(int row, int col, float value) {

    if(!CheckDimension(TWO_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Set(int row, int col, float value) function accepts 2-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return;
    }

    if(row >= 0 && row < this->row && col >= 0 && col < this->col ) {
        arr[0][row][col] = value;
        return;
    }     
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;

}

/*
    void Matrix::Set(int row, int col, int depth, float value)
    Description: Sets the value at the specified row and col locations to the new provided value.
*/

void Matrix::Set(int row, int col, int depth, float value) {

    if(!CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Set(int row, int col, float value) function accepts 3-dimensional matrices, " 
                  << matrixDimension << "-dimensional matrix provided.";
        return;
    }

    if(row >= 0 && row < this->row && col >= 0 && col < this->col && depth >= 0 && depth < this->depth) {
        arr[depth][row][col] = value;
        return;
    }     
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;

}

/*
    void Matrix::Fill(float val)
    Description: Fills the matrix with a specific value.
*/

void Matrix::Fill(float val) {
    for(int i = 0; i < depth; i++)
        for(int j = 0; j < row; j++)
            std::fill(arr[i][j].begin(), arr[i][j].end(), val);
}

/*
    void Matrix::Clear()
    Description: Sets the contents of the matrix to 0.
*/

void Matrix::Clear() {
    for(int i = 0; i < depth; i++)
        for(int j = 0; j < row; j++)
            std::fill(arr[i][j].begin(), arr[i][j].end(), 0.0f);
}

/*
    float Matrix::MaxElement();
    Description: Returns the largest value in the matrix.
*/

float Matrix::MaxElement() {
    float max = Get(0, 0);
    for(int i = 0; i < GetDepth(); i++)
        for(int j = 0; j < GetRow(); j++)
            for(int k = 0; k < GetCol(); k++)
                if(Get(i, j, k) > max)
                    max = Get(i, j, k);
    return max;
    return 0.0f;
}

/*
    float Matrix::MinElement();
    Description: Returns the lowest value in the matrix.
*/

float Matrix::MinElement() {
    float min = Get(0, 0);
    for(int i = 0; i < GetDepth(); i++)
        for(int j = 0; j < GetRow(); j++)
            for(int k = 0; k < GetCol(); k++)
                if(Get(i, j, k) < min)
                    min = Get(i, j, k);
    return min;
}

/*
    void Matrix::Scale(float s, Matrix &mat)
    Description: Scales the provided matrix by the a scalar.
*/

void Matrix::Scale(float s, Matrix &mat) {
    for(int i = 0; i < mat.depth; i++)
        for(int j = 0; j < mat.row; j++)
            for(int k = 0; k < mat.col; k++)
                mat.arr[i][j][k] *= s;
}

/*
    void Matrix::Scale(float s, Matrix &mat, Matrix &out)
    Description: Scales the provided matrix by a scalar, but stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Scale(float s, Matrix &mat, Matrix &out) {
    if(!IsEqualSize(mat, out))
        return;
    for(int i = 0; i < mat.depth; i++)
        for(int j = 0; j < mat.row; j++)
            for(int k = 0; k < mat.col; k++)
                out.Set(i, j, k, mat.Get(i, j, k) * s);
}

/*
    void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Adds two same size matrices together, stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out))
        return;
    for(int i = 0; i < mat1.depth; i++)
        for(int j = 0; j < mat1.row; j++)
            for(int k = 0; k < mat1.col; k++)
                out.Set(i, j, k, mat1.Get(i, j, k) + mat2.Get(i, j, k));
}

/*
    void Matrix::Subtract(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Subtracts two same size matrices together, stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Subtract(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out))
        return;
    for(int i = 0; i < mat1.depth; i++)
        for(int j = 0; j < mat1.row; j++)
            for(int k = 0; k < mat1.col; k++)
                out.Set(i, j, k, mat1.Get(i, j, k) - mat2.Get(i, j, k));
}

/*
    void Matrix::ElementWiseMultiplication(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: As opposed to actual matrix multiplcication, this function multipies
                 each element of a matrix with the element in the same location in mat2.
                 Matrices must be of equal size. Result is stored in the out matrix
                 passed by reference.
*/

void Matrix::ElementWiseMultiplication(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out))
        return;
    for(int i = 0; i < mat1.depth; i++)
        for(int j = 0; j < mat1.row; j++)
            for(int k = 0; k < mat1.col; k++)
                out.Set(i, j, k, mat1.Get(i, j, k) * mat2.Get(i, j, k));
}

/*
    std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat)
    Description: Creates the transpose of the provided matrix.
*/

std::shared_ptr<Matrix> Matrix::C_Transpose(Matrix &mat) {

    if(!mat.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - C_Transpose(Matrix &mat) function accepts 1 or 2-dimensional matrices, " 
                  << mat.matrixDimension << "-dimensional matrix provided.";
        return std::shared_ptr<Matrix>();
    }

    std::shared_ptr<Matrix> out = std::make_shared<Matrix>(mat.col, mat.row);
    for(int i = 0; i < mat.row; i++)
        for(int j = 0; j < mat.col; j++)
            out->Set(i, j, mat.Get(j, i));
    return out;

}

/*
    void Matrix::Transpose(Matrix &mat, Matrix &out)
    Description: Transposes a matrix to an alreaty initialized matrix.
                 The out matrix must be the correct size.
*/

void Matrix::Transpose(Matrix &mat, Matrix &out) {

    if(!mat.CheckDimension(THREE_DIMENSIONAL) || !out.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Transpose(Matrix &mat, Matrix &out) function accepts 1 or 2-dimensional matrices, " 
                  << mat.matrixDimension << "-dimensional and " << out.matrixDimension << "-dimensional matrix provided.";
        return;
    }

    if(!IsEqualSize(mat, out))
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

    if(!mat1.CheckDimension(THREE_DIMENSIONAL) || !mat2.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2) function accepts 1 or 2-dimensional matrices, " 
                  << mat1.matrixDimension << "-dimensional and " << mat2.matrixDimension << "-dimensional matrix provided.";
        return std::shared_ptr<Matrix>();
    }

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

    if(!mat1.CheckDimension(THREE_DIMENSIONAL) || !mat2.CheckDimension(THREE_DIMENSIONAL) || !out.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Product(Matrix &mat1, Matrix &mat2, Matrix &out) function accepts 1 or 2-dimensional matrices, " 
                  << mat1.matrixDimension << "-dimensional, " << mat2.matrixDimension << "-dimensional, and "
                  << out.matrixDimension << "-dimensional matrices provided.";
        return;
    }

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
    bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2)
    Description: Checks if the two provided matrixes are the same size.
*/

bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2) {
    return (mat1.depth == mat2.depth && mat1.row == mat2.row && mat1.col == mat2.col);
}

/*
    bool Matrix::CheckDimension(int targetDimension)
    Description: Checks if the specified matrix is of a specific dimension.
*/

bool Matrix::CheckDimension(EDimension targetDimension) {
    if(targetDimension == EDimension::NULL_DIMENSIONAL)
        return false;
    if(targetDimension == matrixDimension)
        return true;
    return false;
}