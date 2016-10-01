#ifndef VECTOR_H
#define VECTOR_H

class Vector3 {
public:
    double x;
    double y;
    double z;
    
    /**
     * Initializes new Vector3 object as a zero vector;
     *
     * @return Returns new Vector3 object.
     */
    Vector3();
    
    /**
     * Initializes new Vector3 object as a zero vector;
     *
     * @param x X-value of vector
     * @param y Y-value of vector
     * @param z Z-value of vector
     * @return Returns new Vector3 object.
     */
    Vector3(double x, double y, double z);
    
    ~Vector3();
    
    void operator=(const Vector3 &vec);
    Vector3 operator+(const Vector3 &vec); // Vector addition
    Vector3 operator-(const Vector3 &vec); // Vector subtraction
    Vector3 operator*(const double scalar); // Scalar multiple
    Vector3 operator/(const double scalar); // Scalar division
    
    friend ostream& operator<<(ostream& os, const Vector3 &vec);
    
    double getMagnitude();
    Vector3 getNormalized();
    
    /**
     * Returns the dot product of this and 'vec';
     *
     * <p>
     * I could have used Matrix, but that is not necessary
     * since this is quite simple algorithm.
     * </p>
     * @param  vec The vector to be dotted with this vector.
     * @return Dot product of this and 'vec'.
     */
    double dot(Vector3 vec);
    
    /**
     * Returns the cross product of this and 'vec';
     *
     * @param  vec The vector to be crossed with this vector.
     * @return Cross product of this and 'vec'.
     */
    Vector3 cross(Vector3 vec);
    
    double projectScalar(Vector3 vec); // Perform orthogonal scalar projection of this to 'vec'
    Vector3 projectVector(Vector3 vec); // Perform orthogonal vector projection of this to 'vec'
    double angle(Vector3 vec); // Return the angle in radians
    
    void rotate(Vector3 axis, double angle);
};

#endif
