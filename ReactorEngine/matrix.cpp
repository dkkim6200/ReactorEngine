#include "main.hpp"

Matrix::Matrix(int numRow, int numCol) {
    this->numRow = numRow;
    this->numCol = numCol;
    
    m = new float[numRow * numCol];
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            m[i * numCol + j] = 0.0;
        }
    }
}

Matrix::Matrix(int numRow, int numCol, float *args) {
    this->numRow = numRow;
    this->numCol = numCol;
    
    m = new float[numRow * numCol];
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            m[i * numCol + j] = args[i * numCol + j];
        }
    }
}

Matrix::~Matrix() {
    delete [] m;
}

void Matrix::operator=(const Matrix &mat) {
    if (numRow == mat.numRow && numCol == mat.numCol) {
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                m[i * numCol + j] = mat.m[i * numCol + j];
            }
        }
    }
}

Matrix Matrix::operator+(const Matrix &mat) {
    Matrix result = Matrix(numRow, numCol);
    
    if (numRow == mat.numRow && numCol == mat.numCol) {
        for (int i = 0; i < numRow; i++) {
            for (int j = 0; j < numCol; j++) {
                result.m[i * numCol + j] = m[i * numCol + j] + mat.m[i * numCol + j];
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
                result.m[i * numCol + j] = m[i * numCol + j] - mat.m[i * numCol + j];
            }
        }
    }
    
    return result;
}

Matrix Matrix::operator*(const float scalar) {
    Matrix result = Matrix(numRow, numCol);
    
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            result.m[i * numCol + j] = m[i * numCol + j] * scalar;
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
                    result.m[i * numCol + j] += (*this).m[i * numCol + k] * mat.m[k * numCol + j];
                }
            }
        }
    }
    
    return result;
}

Matrix Matrix::operator*(const Vector3 &vec) {
    return (*this) * Matrix(3, 1,
                            (float[]) {
                                vec.x,
                                vec.y,
                                vec.z });
}

ostream& operator<<(ostream& os, const Matrix &mat) {
    for (int i = 0; i < mat.numRow; i++) {
        os << "[";
        for (int j = 0; j < mat.numCol; j++) {
            os << " " << mat.m[i * mat.numCol + j] << " ";
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

float Matrix::get(int row, int col) {
    return m[row * numCol + col];
}

void Matrix::set(int row, int col, float value) {
    m[row * numCol + col] = value;
}

Matrix Matrix::getRotationMat(Quaternion q) {
    Matrix rotationMat = Matrix (4, 4, (float[]) {
        static_cast<float>(1 - 2*(q.y*q.y + q.z*q.z)),          static_cast<float>(2*(q.x * q.y - q.w * q.z)),  static_cast<float>(2*(q.w * q.y + q.x * q.z)),  0,
        static_cast<float>(2*(q.x * q.y + q.w * q.z)),          static_cast<float>(1 - 2*(q.x*q.x + q.z*q.z)),  static_cast<float>(2*(q.y * q.z - q.w * q.x)),  0,
        static_cast<float>(2*(q.x * q.z - q.w * q.y)),          static_cast<float>(2*(q.w * q.x + q.y * q.z)),  static_cast<float>(1 - 2*(q.x*q.x + q.y*q.y)),  0,
        0,                                                      0,                                              0,                                              1});
    
    return rotationMat;
}

Matrix Matrix::getTranslationMat(Vector3 translationVec) {
    Matrix translationMat = Matrix (4, 4, (float[]) {
        1.0f, 0.0f, 0.0f, translationVec.x,
        0.0f, 1.0f, 0.0f, translationVec.y,
        0.0f, 0.0f, 1.0f, translationVec.z,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    
    return translationMat;
}

Matrix Matrix::getScaleMat(Vector3 scaleVec) {
    Matrix scaleMat = Matrix (4, 4, (float[]) {
        scaleVec.x, 0.0f,       0.0f,       0.0f,
        0.0f,       scaleVec.y, 0.0f,       0.0f,
        0.0f,       0.0f,       scaleVec.z, 0.0f,
        0.0f,       0.0f,       0.0f,       1.0f
    });
    
    return scaleMat;
}


Matrix Matrix::getProjectionMat(float aspectRatio, float zNear, float zFar, float fov) {
    Matrix projectionMat = Matrix (4, 4, (float[]) {
        1.0f / (aspectRatio * tan(fov / 2)), 0,                   0,                            0,
        0,                                   1.0f / tan(fov / 2), 0,                            0,
        0,                                   0,                   (-zNear-zFar) / (zNear-zFar), (2*zFar*zNear) / (zNear-zFar),
        0,                                   0,                   1,                            0
    });
    
    return projectionMat;
}
