#ifndef VECTOR_HPP
#define VECTOR_HPP

class Quaternion;

class Vector3 {
public:
    float x;
    float y;
    float z;
    
    /**
     @brief Initializes new Vector3 object as a zero vector;
     
     @return Returns new Vector3 object.
     */
    Vector3();
    
    /**
     @brief Initializes new Vector3 object as a zero vector;
     
     @param x X-value of vector
     @param y Y-value of vector
     @param z Z-value of vector
     @return Returns new Vector3 object.
     */
    Vector3(float x, float y, float z);
    
    ~Vector3();
    
    void operator=(const Vector3 &vec);
    Vector3 operator+(const Vector3 &vec); // Vector addition
    Vector3 operator+=(const Vector3 &vec);
    Vector3 operator-(const Vector3 &vec); // Vector subtraction
    Vector3 operator-=(const Vector3 &vec);
    Vector3 operator*(const float scalar); // Scalar multiple
    Vector3 operator/(const float scalar); // Scalar division
    
    friend ostream& operator<<(ostream& os, const Vector3 &vec);
    
    /**
     @brief Returns the magnitude of this vector.
     
     @return Magnitude of this Vector3 in float
     */
    float getMagnitude();
    
    Quaternion getQuaternion();
    
    /**
     @brief Normalizes this vector.
     
     WARNING! This function alters the current state of this vector!
     */
    Vector3 normalize();
    
    /**
     @brief Returns the dot product of this and 'vec'.
     
     
     I could have used Matrix, but that is not necessary
     since this is quite simple algorithm.
     
     @param  vec The vector to be dotted with this vector.
     @return Dot product of this and 'vec'.
     */
    float dot(Vector3 vec);
    
    /**
     @brief Returns the cross product of this and 'vec';
     
     @param  vec The vector to be crossed with this vector.
     @return Cross product of this and 'vec'.
     */
    Vector3 cross(Vector3 vec);
    
    /**
     @brief Perform orthogonal scalar projection of this to 'vec'
     
     @param vec Vector for this to be projected to
     @return Projected scalar value
     */
    float projectScalar(Vector3 vec);
    
    /**
     @brief Perform orthogonal vector projection of this to 'vec'
     
     @param vec Vector for this to be projected to
     @return Projected vector
     */
    Vector3 projectVector(Vector3 vec);
    
    /**
     @brief Returns angle between this and 'vec'
     
     @param vec Vector to be used to calculate the angle
     @return Angle between this and 'vec'
     */
    float angle(Vector3 vec); // Return the angle in radians
    
    /**
     @brief Rotates this vector.
     
     The rotation matrix used (from [2]):
     @code
     [ cosA  -sinA  0  ][ cosB  0 sinB ][ 1   0      0  ][ x ]
     [ sinA  cosA   0  ][  0    1  0   ][ 0  cosY -sinY ][ y ]
     [ 0     0      1  ][ -sinB 0 cosB ][ 0  sinY  cosY ][ z ]
     @endcode
     whose yaw(around Z-axis), pitch(around Y-axis) and roll(around X-axis) angles are A(alpha), B(beta) and Y(gamma).
     
     WHY IS THE ROTATION MATRIX ABOVE NOT WORKING?????
     OHHH Gimbal Lock!!!
     
     For now, I'm rotating the vector around Z-axis, then Y-axis, then X-axis.
     
     @see http://stackoverflow.com/questions/5207708/rotation-in-a-vector2d-class-in-java
     @see https://en.wikipedia.org/wiki/Rotation_matrix
     @see http://mathworld.wolfram.com/RotationMatrix.html
     @see http://www.iue.tuwien.ac.at/phd/wessner/node42.html
     @see http://www.nh.cas.cz/people/lazar/celler/online_tools.php?start_vec=100,100,100&rot_ax=60,30,20&rot_ang=150
     @see https://docs.unity3d.com/ScriptReference/Transform.Rotate.html
     
     @warning It alters the current vector.
     
     @param  axis Axis of which this vector is to rotate around
     @param  angle Amount of angle to rotate
     */
    void rotate(Vector3 axis, float angle);
};

#endif
