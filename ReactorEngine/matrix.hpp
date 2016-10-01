#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
protected:
    int numRow;
    int numCol;
    double **matrix;
    
public:
    Matrix(int numRow, int numCol);
    Matrix(int numRow, int numCol, double *args);
    ~Matrix();
    
    void operator=(const Matrix &mat);
    Matrix operator+(const Matrix &mat); // Matrix addition
    Matrix operator-(const Matrix &mat); // Matrix subtraction
    Matrix operator*(const double scalar); // Scalar multiplication
    Matrix operator*(const Matrix &mat); // Matrix multiplication
    Matrix operator*(const Vector3 &vec);
    
    friend ostream& operator<<(ostream& os, const Matrix &mat);
    
    int getNumRow();
    int getNumCol();
    
    double get(int row, int col);
    void set(int row, int col, double value);
};

#endif
