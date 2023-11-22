#include "../header/Matrix.h"

/*
    Matrix::Matrix(int row_, bool isHorizontalVector_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int length, bool isHorizontalVector_) :
    isHorizontalVector(isHorizontalVector_) {
    arr.resize(1);
    row = 1; col = 1;
    if(!isHorizontalVector)
        row = length;
    else
        col = length;
    depth = 1;
    matrixDimension = ONE_DIMENSIONAL;
    if(!isHorizontalVector) {
        arr[0].resize(length);
        for(int i = 0; i < length; i++)
            arr[0][i].resize(1);
    } else {
        arr[0].resize(1);
        arr[0][0].resize(length);
    }
}

/*
    Matrix::Matrix(int row_, int col_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int row_, int col_) :
    row(row_), col(col_) {
    depth = 1;
    matrixDimension = TWO_DIMENSIONAL;
    arr.resize(1);
    arr[0].resize(row);
    for(int i = 0; i < row; i++)
        arr[0][i].resize(col);
    if(row_ == 1 || col_ == 1)
        matrixDimension = ONE_DIMENSIONAL;
}

/*
    Matrix::Matrix(int depth_, int row_, int col_)
    Description: Constructor of the matrix class, defines the size of the matrix
                 and initializes it.
*/

Matrix::Matrix(int depth_, int row_, int col_) :
    row(row_), col(col_), depth(depth_) {
    arr.resize(depth);
    matrixDimension = THREE_DIMENSIONAL;
    for(int i = 0; i < depth; i++) {
        arr[i].resize(row);
        for(int j = 0; j < row; j++)
            arr[i][j].resize(col);
    }
    int dimensionCount = 3;
    if(depth_ == 1)
        dimensionCount--;
    if(row_ == 1)
        dimensionCount--;
    if(col_ == 1)
        dimensionCount--;
    matrixDimension = (EDimension)dimensionCount;
}

/*
    std::shared_ptr<Matrix> Matrix::CreateMatrix(Matrix &m, bool copyElements);
    Description: Creates a new matrix based on the matrix provided. The size will be equivalent,
                 and if copyElements is true, the elements will also be equivalent. If copyElements
                 is false, then the elements of the new matrix will remain as zero.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(Matrix &m, bool copyElements) {
    std::shared_ptr<Matrix> result = CreateMatrix(m.depth, m.row, m.col);
    result->isHorizontalVector = m.isHorizontalVector;
    if(copyElements);
        Matrix::CopyData(m, *result.get());
    return result;
}

/*
    std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int isHorizontalVector)
    Description: Creates a matrix with the specified matrix row and orientation.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int length, bool isHorizontalVector) {
    return std::make_shared<Matrix>(length, isHorizontalVector);
}


/*
    std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int col)
    Description: Creates a matrix with the specified matrix row and col size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int row, int col) {
    return std::make_shared<Matrix>(row, col);
}

/*
    std::shared_ptr<Matrix> Matrix::CreateMatrix(int depth, int row, int col)
    Description: Creates a matrix with the specified matrix row, col, and depth size.
*/

std::shared_ptr<Matrix> Matrix::CreateMatrix(int depth, int row, int col) {
    return std::make_shared<Matrix>(depth, row, col);
}

/*
    int Matrix::AddData(py::array_t<float> data)
    Description: Adds the information from the provided array into the matrix. Returns
                 an index where the copy ended. If the index is less than the size of data, then
                 the matrix was filled with values, and there was more elements in data. If it is
                 the same size as the size of data, then the matrix was filled while using every element
                 in data. A return index of -1 indicates that there weren't enough elements in index to
                 add to every element in the matrix.
*/

int Matrix::AddData(py::array_t<float> &data) {
    int index = 0;
    for(int i = 0; i < depth; i++)
        for(int j = 0; j < row; j++)
            for(int k = 0; k < col; k++) {
                if(index == data.size())
                    return -1;
                arr[i][j][k] = data.at(index);
                index++;
            }
    return index;
}

/*
    int Matrix::AddData(std::vector<float> data)
    Description: Adds the information from the provided array into the matrix. Returns
                 an index where the copy ended. If the index is less than the size of data, then
                 the matrix was filled with values, and there was more elements in data. If it is
                 the same size as the size of data, then the matrix was filled while using every element
                 in data. A return index of -1 indicates that there weren't enough elements in index to
                 add to every element in the matrix.
*/

int Matrix::AddData(std::vector<float> &data) {
    int index = 0;
    for(int i = 0; i < depth; i++)
        for(int j = 0; j < row; j++)
            for(int k = 0; k < col; k++) {
                if(index == data.size())
                    return -1;
                arr[i][j][k] = data[index];
                index++;
            }
    return index;
}

/*
    Matrix::CopyData(Matrix &copy, Matrix &out)
    Description: Copies data from the provided "copy" matrix and stores the result in the provided
                 "out" matrix. NOTE: Matrices must be of equal size.
*/

void Matrix::CopyData(Matrix &copy, Matrix &out) {
    
    if(!IsEqualSize(copy, out)) {
        std::cout << "Matrix.cpp - [ERROR] - CopyData(Matrix &copy, Matrix &out) - Matrices are not of equal size." << std::endl;
        return;
    }

    for(int i = 0; i < copy.depth; i++)
        for(int j = 0; j < copy.row; j++)
            for(int k = 0; k < copy.col; k++)
                out.Set(i, j, k, copy.Get(i, j, k));

}

/*
    float Matrix::Get(int index)
    Description: Returns the value from a vector at the specified index.
*/

float Matrix::Get(int index) {

    if(!isHorizontalVector) {
        if(index >= 0 && index < row)
            return arr[0][index][0];
    } else {
        if(index >= 0 && index < col)
            return arr[0][0][index];
    }

    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds.\n" << std::endl;
    return 0.0f;

}

/*
    float Matrix::Get(int row, int col)
    Description: Returns the value at the specified row and col locations.
*/

float Matrix::Get(int row, int col) {

    if(row >= 0 && row < this->row && col >= 0 && col < this->col )
        return arr[0][row][col];
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;
    return 0.0f;

}

/*
    float Matrix::Get(int depth, int row, int col)
    Description: Returns the value at the specified row, col, and depth locations.
*/

float Matrix::Get(int depth, int row, int col) {

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

    if(!isHorizontalVector) {
        if(index >= 0 && index < row)
            arr[0][index][0] = value;
        return;
    } else {
        if(index >= 0 && index < col)
            arr[0][0][index] = value;
        return;
    }

    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;

}

/*
    void Matrix::Set(int row, int col, float value)
    Description: Sets the value at the specified row and col locations to the new provided value.
*/

void Matrix::Set(int row, int col, float value) {

    if(row >= 0 && row < this->row && col >= 0 && col < this->col ) {
        arr[0][row][col] = value;
        return;
    }     
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;

}

/*
    void Matrix::Set(int depth, int row, int col, float value)
    Description: Sets the value at the specified row and col locations to the new provided value.
*/

void Matrix::Set(int depth, int row, int col, float value) {

    if(row >= 0 && row < this->row && col >= 0 && col < this->col && depth >= 0 && depth < this->depth) {
        arr[depth][row][col] = value;
        return;
    }     
    std::cout << "Matrix.cpp - [ERROR] - Index out of bounds." << std::endl;

}

/*
    bool Matrix::Empty()
    Description: Returns true the matrix isn't initialized in any shape or form.
*/

bool Matrix::Empty() {
    return (depth == 0 || row == 0 || col == 0);
}

/*
    bool Matrix::IsLocationInBounds(int d, int r, int c)
    Description: Returns true of the provided indices are within the bounds of
                 the matrix, returns false otherwise.
*/

bool Matrix::IsLocationInBounds(int d, int r, int c) {
    return ( d >= 0 && d < depth &&
             c >= 0 && c < col &&
             r >= 0 && r < row );
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
    Fill(0.0f);
}

/*
    float Matrix::MaxElement();
    Description: Returns the largest value in the matrix.
*/

float Matrix::MaxElement() {
    float max = Get(0, 0, 0);
    for(int i = 0; i < GetDepth(); i++)
        for(int j = 0; j < GetRow(); j++)
            for(int k = 0; k < GetCol(); k++)
                if(Get(i, j, k) > max)
                    max = Get(i, j, k);
    return max;
}

/*
    float Matrix::MaxElement();
    Description: Returns the largest value in the matrix, along with the
                 index of the location of that value in the matrix.
*/

float Matrix::MaxElement(int &d, int &r, int &c) {
    d = 0; r = 0; c = 0;
    float max = Get(0, 0, 0);
    for(int i = 0; i < GetDepth(); i++) {
        for(int j = 0; j < GetRow(); j++) {
            for(int k = 0; k < GetCol(); k++) {
                if(Get(i, j, k) > max) {
                    max = Get(i, j, k);
                    d = i; r = j; c = k;
                }
            }
        }
    }
    return max;
}

/*
    float Matrix::MinElement();
    Description: Returns the lowest value in the matrix.
*/

float Matrix::MinElement() {
    float min = Get(0, 0, 0);
    for(int i = 0; i < GetDepth(); i++)
        for(int j = 0; j < GetRow(); j++)
            for(int k = 0; k < GetCol(); k++)
                if(Get(i, j, k) < min)
                    min = Get(i, j, k);
    return min;
}

/*
    EDimension Matrix::GetDimension()
    Description: Returns the dimension type of the matrix.
*/

EDimension Matrix::GetDimension() {
    return matrixDimension;
}

/*
    void Matrix::Scale(float s)
    Description: Scales the provided matrix by the a scalar.
*/

void Matrix::Scale(float s) {
    for(int i = 0; i < depth; i++)
        for(int j = 0; j < row; j++)
            for(int k = 0; k < col; k++)
                arr[i][j][k] *= s;
}

/*
    void Matrix::Scale(float s, Matrix &mat, Matrix &out)
    Description: Scales the provided matrix by a scalar, but stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Scale(float s, Matrix &mat, Matrix &out) {
    if(!IsEqualSize(mat, out)) {
        std::cout << "Matrix.cpp - [ERROR] - Scale(float s, Matrix &mat, Matrix &out) - Provided"
                  << " matrices are not of equal size." << std::endl;
        return;
    }

    for(int i = 0; i < mat.depth; i++)
        for(int j = 0; j < mat.row; j++)
            for(int k = 0; k < mat.col; k++)
                out.Set(i, j, k, mat.Get(i, j, k) * s);
}

/*
    bool Matrix::Equals(Matrix &mat1, Matrix &mat2)
    Description: Returns true if both provided matrices are identical, false otherwise.
*/

bool Matrix::Equals(Matrix &mat1, Matrix &mat2) {

    if(!IsEqualSize(mat1, mat2))
        return false;

    for(int i = 0; i < mat1.depth; i++)
        for(int j = 0; j < mat1.row; j++)
            for(int k = 0; k < mat1.col; k++)
                if(mat1.arr[i][j][k] != mat2.arr[i][j][k])
                    return false;

    return true;

}

/*
    bool Matrix::EqualsWithinMargin(Matrix &mat1, Matrix &mat2, float delta)
    Description: Returns true if both provided matrices are identical, values may differ
                 within the provided delta value.
*/

bool Matrix::EqualsWithinMargin(Matrix &mat1, Matrix &mat2, float delta) {

    if(!IsEqualSize(mat1, mat2))
        return false;

    for(int i = 0; i < mat1.depth; i++)
        for(int j = 0; j < mat1.row; j++)
            for(int k = 0; k < mat1.col; k++)
                if(std::abs(mat1.arr[i][j][k] - mat2.arr[i][j][k]) > delta)
                    return false;

    return true;

}

/*
    void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Adds two same size matrices together, stores the result in
                 the out matrix passed by reference.
*/

void Matrix::Add(Matrix &mat1, Matrix &mat2, Matrix &out) {
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out)) {
        std::cout << "Matrix.cpp - [ERROR] - Add(Matrix &mat1, Matrix &mat2, Matrix &out) - Provided"
                  << " matrices are not of equal size." << std::endl;
        return;
    }

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
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out)) {
        std::cout << "Matrix.cpp - [ERROR] - Subtract(Matrix &mat1, Matrix &mat2, Matrix &out) - Provided"
                  << " matrices are not of equal size." << std::endl;
        return;
    }

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
    if(!IsEqualSize(mat1, mat2) || !IsEqualSize(mat2, out)) {
        std::cout << "Matrix.cpp - [ERROR] - ElementWiseMultiplication(Matrix &mat1, Matrix &mat2, Matrix &out) - Provided"
                  << " matrices are not of equal size." << std::endl;
        return;
    }
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

    if(mat.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - C_Transpose(Matrix &mat) function accepts 1 or 2-dimensional matrices, " 
                  << mat.matrixDimension << "-dimensional matrix provided.\n";
        return std::shared_ptr<Matrix>();
    }

    std::shared_ptr<Matrix> out = std::make_shared<Matrix>(mat.col, mat.row);
    for(int i = 0; i < out->row; i++)
        for(int j = 0; j < out->col; j++)
            out->Set(i, j, mat.Get(j, i));
    return out;

}

/*
    void Matrix::Transpose(Matrix &mat, Matrix &out)
    Description: Transposes a matrix to an alreaty initialized matrix.
                 The out matrix must be the correct size.
*/

void Matrix::Transpose(Matrix &mat, Matrix &out) {

    if(mat.CheckDimension(THREE_DIMENSIONAL) || out.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Transpose(Matrix &mat, Matrix &out) function accepts 1 or 2-dimensional matrices, " 
                  << mat.matrixDimension << "-dimensional and " << out.matrixDimension << "-dimensional matrices provided.\n";
        return;
    }

    if(mat.row != out.col || out.row != mat.col)
        return;

    for(int i = 0; i < out.row; i++)
        for(int j = 0; j < out.col; j++)
            out.Set(i, j, mat.Get(j, i));

}

/*
    std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2)
    Description: Creates a matrix that is the size of what the resulting size form the product
                 of the two provided matrices would be.
*/

std::shared_ptr<Matrix> Matrix::C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2) {

    if(mat1.CheckDimension(THREE_DIMENSIONAL) || mat2.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - C_EmptyProductMatrix(Matrix &mat1, Matrix &mat2) function accepts 1 or 2-dimensional matrices, " 
                  << mat1.matrixDimension << "-dimensional and " << mat2.matrixDimension << "-dimensional matrices provided.\n";
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

    if(mat1.CheckDimension(THREE_DIMENSIONAL) || mat2.CheckDimension(THREE_DIMENSIONAL) || out.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - Product(Matrix &mat1, Matrix &mat2, Matrix &out) function accepts 1 or 2-dimensional matrices, " 
                  << mat1.matrixDimension << "-dimensional, " << mat2.matrixDimension << "-dimensional, and "
                  << out.matrixDimension << "-dimensional matrices provided.\n";
        return;
    }

    if(mat1.col != mat2.row) {
        std::cout << "Matrix.cpp - [ERROR] - Matrix multiplication imposible with given matrices" << std::endl;
        return;
    }

    for (int i = 0; i < mat1.row; i++) {
        for (int j = 0; j < mat2.col; j++) {
            float result = 0.0f;
            for (int k = 0; k < mat1.col; k++) {
                result += mat1.Get(i, k) * mat2.Get(k, j);
            }
            out.Set(i, j, result);
        }
    }

}

/*
    void Matrix::AccumulateProduct(Matrix &mat1, Matrix &mat2, Matrix &out)
    Description: Performs matrix multiplication and adds the result to the out matrix.
*/

void Matrix::AccumulateProduct(Matrix &mat1, Matrix &mat2, Matrix &out) {

    if(mat1.CheckDimension(THREE_DIMENSIONAL) || mat2.CheckDimension(THREE_DIMENSIONAL) || out.CheckDimension(THREE_DIMENSIONAL)) {
        std::cout << "Matrix.cpp - [ERROR] - AccumulateProduct(Matrix &mat1, Matrix &mat2, Matrix &out) function accepts 1 or 2-dimensional matrices, " 
                  << mat1.matrixDimension << "-dimensional, " << mat2.matrixDimension << "-dimensional, and "
                  << out.matrixDimension << "-dimensional matrices provided.\n";
        return;
    }

    if(mat1.col != mat2.row) {
        std::cout << "Matrix.cpp - [ERROR] - Matrix multiplication imposible with given matrices" << std::endl;
        return;
    }

    for (int i = 0; i < mat1.row; i++) {
        for (int j = 0; j < mat2.col; j++) {
            float result = 0.0f;
            for (int k = 0; k < mat1.col; k++) {
                result += mat1.Get(i, k) * mat2.Get(k, j);
            }
            out.Set(i, j, out.Get(i, j) + result);
        }
    }

}

/*
    std::shared_ptr<Matrix> Matrix::C_EmptyConvolutionMatrix(bool convolutionType, Matrix &in, Matrix &kernels)
    Description: Creates a matrix that will be properly sized to perform the convolution function of the
                 with the given convolution type, data size, and kernel size.

    NOTE: CURRENTLY INCORRECT. DO NOT USE.
*/

std::shared_ptr<Matrix> Matrix::C_EmptyConvolutionMatrix(bool convolutionType, Matrix &in, Matrix &kernels) {

    std::cout << "C_EmptyConvolutionMatrix is incorrect. Do not use." << std::endl;

    if(kernels.GetRow() != kernels.GetCol())
        return std::shared_ptr<Matrix>();

    if(kernels.GetRow() > in.GetRow() || kernels.GetCol() > in.GetCol())
        return std::shared_ptr<Matrix>();

    int kernelSize = kernels.GetRow();
    int depth, row, col;
    depth = in.GetDepth() * kernels.GetDepth();
    if(convolutionType == STANDARD_CONVOLUTION) {
        row = in.GetRow() - kernelSize + 1;
        col = in.GetCol() - kernelSize + 1;
    } else {
        row = in.GetRow() + kernelSize - 1;
        col = in.GetCol() + kernelSize - 1;
    }

    return std::make_shared<Matrix>(depth, row, col);

}

/*
    void Matrix::Convolution(bool convolutionType, Matrix &in, Matrix &kernels, Matrix &out)
    Description: Performs convolution given a matrix of images, and a matrix of kernels.
                 The output will also be a matrix containing in.depth * kernels.depth images.
                 Essentially, the number of input images times the number of kernels.

    NOTE: The output matrix shape varies based on the input, use C_EmptyConvolutionMatrix to
    create a properly sized matrix for the operation you want to perform.
*/

void Matrix::Convolution(bool convolutionType, Matrix &in, Matrix &kernels, Matrix &out, int outputChannel) {

    if(in.GetDepth() != kernels.GetDepth()) {
        std::cout << "[ERROR] - Convoltuion - in.GetDepth() != kernels.GetDepth()" << std::endl;
        return;
    }

    int startRow, startCol;
    int endRow, endCol;
    int kernelSize = kernels.GetRow();
    int inputChannels = in.GetDepth();

    if(convolutionType == STANDARD_CONVOLUTION)
        startRow = startCol = 0;
    else
        startRow = startCol = -((kernelSize % 2) + 1);

    endRow = endCol = out.GetCol() + startRow;

    for(int i = startRow; i < endRow; i++)
        for(int j = startCol; j < endCol; j++)
            out.Set(outputChannel, i, j, 
                    ConvolveIndex(i, j, in, kernels) + out.Get(outputChannel, i, j));

}

/*
    bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2)
    Description: Checks if the two provided matrixes are the same size.
*/

bool Matrix::IsEqualSize(Matrix &mat1, Matrix &mat2) {
    return (mat1.depth == mat2.depth && mat1.row == mat2.row && mat1.col == mat2.col);
}

/*
    float Matrix::ConvolveIndex(int rowIndex, int colIndex, int channel, int kernelChannel,
                                Matrix &in, Matrix &kernels);
    Description: Calculates the resulting value from the kernel location and returns it.
*/

float Matrix::ConvolveIndex(int rowIndex, int colIndex, Matrix &in, Matrix &kernel) {

    int kernelSize = kernel.GetRow();
    int depth = in.GetDepth();
    float result = 0.0f;
    for(int i = rowIndex; i < rowIndex + kernelSize; i++)
        for(int j = colIndex; j < colIndex + kernelSize; j++) {
            if(i < 0 || i >= in.GetRow() || j < 0 || j >= in.GetCol())
                continue;
            for(int k = 0; k < depth; k++)
                result += in.Get(depth, i, j) * kernel.Get(depth, i - rowIndex, j - colIndex);
        }

    return result;

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

/*
    std::ostream &operator<<(std::ostream &os, const Matrix &m);
    Description: Operation overloader for printing object to console.
                 Prints the shape of the matrix to the console.
*/

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    os << "(" << m.GetDepth() << ", " << m.GetRow() << ", " << m.GetCol() << ")";
    return os;
}