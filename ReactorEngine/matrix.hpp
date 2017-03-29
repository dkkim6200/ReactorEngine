#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
protected:
    int numRow;
    int numCol;
    
public:
    float *m;
    
    /**
     @brief Initialize this Matrix as a zero-filled matrix.
     
     @param numRow Number of rows
     @param numCol Number of columns
     */
    Matrix(int numRow, int numCol);
    
    /**
     @brief Initialize this Matrix as the values given as arguments.

     The recommended way of providing the array for parameter "args" is as followed:<br>
     @code
     Matrix(... , (float[]){ 1, 2, 3, ... });
     @endcode
     
     @param numRow Number of rows
     @param numCol Number of columns
     @param args Array of floating-point values for this Matrix to initialize with.
     */
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
    
    /**
     @brief Returns the value of matrix element at (row, col).
     
     @param row Row that the element is at
     @param col Column that the element is at
     @return Matrix element at (row, col)
     */
    float get(int row, int col);
    
    /**
     @brief Sets the value of matrix element at (row, col).
     
     @param row Row that the destination element is at
     @param col Column that the destination element is at
     */
    void set(int row, int col, float value);
    
    /**
     @brief Returns a rotation matrix matching the rotation given by 'q'
     
     @param q Quaternion representing the rotation
     @return Rotation matrix matching the rotation given by 'q'
     */
    static Matrix getRotationMat(Quaternion q);
    
    /**
     @brief Returns a translation matrix.
     
     @param translationVec Vector of the amount of translation
     @return Translation matrix with the values given by translationVec
     */
    static Matrix getTranslationMat(Vector3 translationVec);
    
    /**
     @brief Returns a scale matrix.
     
     @param scaleVec Vector of the amount of scale
     @return Scale matrix with the values given by scaleVec
     */
    static Matrix getScaleMat(Vector3 scaleVec);
    
    /**
     @brief Returns a projection matrix.
     
     @param aspectRatio Aspect ratio of the screen; equivalent of (Screen Width) / (Screen Height)
     @param nearZ Z-plane of which the objects that are too close are to be clipped past this plane
     @param farZ Z-plane of which the objects that are too far are to be clipped past this plane
     @param fov Angle of Field-of-view of the camera in radians
     @return Projection matrix for the camera
     */
    static Matrix getProjectionMat(float aspectRatio, float nearZ, float farZ, float fov);
};

#endif
