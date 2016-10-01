#include "main.h"

Matrix::Matrix(int numRow, int numCol) {
    this->numRow = numRow;
    this->numCol = numCol;
    
    matrix = new double*[numRow];
    for (int i = 0; i < numRow; i++) {
        matrix[i] = new double[numCol];
        
        for (int j = 0; j < numCol; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int numRow, int numCol, double *args) {
    this->numRow = numRow;
    this->numCol = numCol;
    
    matrix = new double*[numRow];
    for (int i = 0; i < numRow; i++) {
        matrix[i] = new double[numCol];
        
        for (int j = 0; j < numCol; j++) {
            matrix[i][j] = args[i * numCol + j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < numRow; i++) {
        delete [] matrix[i];
    }
    
    delete [] matrix;
}

void Matrix::operator=(const Matrix &mat) {
    if (numRow == mat.numRow && numCol == mat.numCol) {
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                matrix[i][j] = mat.matrix[i][j];
            }
        }
    }
}

Matrix Matrix::operator+(const Matrix &mat) {
    Matrix result = Matrix(numRow, numCol);
    
    if (numRow == mat.numRow && numCol == mat.numCol) {
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                result.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
            }
        }
    }
    
    return result;
}

Matrix Matrix::operator-(const Matrix &mat) {
    Matrix result = Matrix(numRow, numCol);
    
    if (numRow == mat.numRow && numCol == mat.numCol) {
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                result.matrix[i][j] = matrix[i][j] - mat.matrix[i][j];
            }
        }
    }
    
    return result;
}

Matrix Matrix::operator*(const double scalar) {
    Matrix result = Matrix(numRow, numCol);
    
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    
    return result;
}

Matrix Matrix::operator*(const Matrix &mat) {
    int m = numRow;
    int n = mat.numCol;
    
    Matrix result = Matrix(m, n);
    
    if (numCol == mat.numRow) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < numCol; k++) {
                    result.matrix[i][j] += (*this).matrix[i][k] * mat.matrix[k][j];
                }
            }
        }
    }
    
    return result;
}

Matrix Matrix::operator*(const Vector3 &vec) {
    return (*this) * Matrix(3, 1,
                            (double[]) {
                                vec.x,
                                vec.y,
                                vec.z });
}

ostream& operator<<(ostream& os, const Matrix &mat) {
    for (int i = 0; i < mat.numRow; i++) {
        os << "[";
        for (int j = 0; j < mat.numCol; j++) {
            os << " " << mat.matrix[i][j] << " ";
        }
        os << "]\n";
    }
    
    return os;
}

int Matrix::getNumRow() {
    return numRow;
}

int Matrix::getNumCol() {
    return numCol;
}

double Matrix::get(int row, int col) {
    return matrix[row][col];
}

void Matrix::set(int row, int col, double value) {
    matrix[row][col] = value;
}