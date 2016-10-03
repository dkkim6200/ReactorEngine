#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
protected:
    int numRow;
    int numCol;
    
public:
    float *m;
    
    Matrix(int numRow, int numCol);
    Matrix(int numRow, int numCol, float *args);
    ~Matrix();
    
    void operator=(const Matrix &mat);
    Matrix operator+(const Matrix &mat); // Matrix addition
    Matrix operator-(const Matrix &mat); // Matrix subtraction
    Matrix operator*(const float scalar); // Scalar multiplication
    Matrix operator*(const Matrix &mat); // Matrix multiplication
    Matrix operator*(const Vector3 &vec);
    
    friend ostream& operator<<(ostream& os, const Matrix &mat);
    
    int getNumRow();
    int getNumCol();
    
    float get(int row, int col);
    void set(int row, int col, float value);
};

#endif
