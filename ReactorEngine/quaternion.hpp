#ifndef QUATERNION_HPP
#define QUATERNION_HPP

class Quaternion {
public:
    double x;
    double y;
    double z;
    double w;
    
    /**
     @brief Initiates a identity quaternion.
     */
    Quaternion();
    
    /**
     @brief Initiates a quaternion with x, y, z, and w values.
     
     @param x X (Coefficient of i) value of this quaternion
     @param y Y (Coefficient of j) value of this quaternion
     @param z Z (Coefficient of k) value of this quaternion
     @param w W (Scalar part) value of this quaternion
     */
    Quaternion(double x, double y, double z, double w);
    
    /**
     @brief Initiates a rotation quaternion with 3 Euler angles.
     
     @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
     
     @param xRot Rotation along the x-axis in radian
     @param yRot Rotation along the y-axis in radian
     @param zRot Rotation along the z-axis in radian
     */
    Quaternion(double xRot, double yRot, double zRot);
    
    /**
     @brief Initiates a rotaiton quaternion from axis-angle rotation.
     
     @param axis The axis, in vector, in which the rotation shall occur
     @param angle The angle of rotaiton around the axis
     */
    Quaternion(Vector3 axis, double angle);
    
    /**
     @brief Returns a rotation quaternion of an identity rotation.
     
     @return Identity quaternion
     */
    static Quaternion identity();
    
    Quaternion operator*(const Vector3 vec);
    Quaternion operator*(const Quaternion quat);
    
    friend ostream& operator<<(ostream& os, const Quaternion &q);
    
    /**
     @brief Returns the vector part (x, y, z) of this quaternion.
     
     @return Vector part of this quaternion
     */
    Vector3 getVector();
    
    /**
     @brief Normalizes this quaternion.
     
     WARNING! This function alters the current state of this quaternion!
     */
    void normalize();
    
    /**
     @brief Returns the conjugate of this quaternion.
     
     @return Conjugate of this quaternion
     */
    Quaternion getConjugate();
    
    /**
     @brief Converts this quaternion to 3 euler angles respectively to each of the 3 axis.
     
     @return Vector3 of euler angles, where each represents the rotation on each of 3 axis
     */
    Vector3 toEulerAngles();
};

#endif
