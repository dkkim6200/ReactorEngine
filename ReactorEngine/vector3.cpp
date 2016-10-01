#include "main.h"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::~Vector3() {
}

void Vector3::operator=(const Vector3 &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector3 Vector3::operator+(const Vector3 &vec) {
    Vector3 result = Vector3(x + vec.x, y + vec.y, z + vec.z);
    return result;
}

Vector3 Vector3::operator-(const Vector3 &vec) {
    Vector3 result = Vector3(x - vec.x, y - vec.y, z - vec.z);
    return result;
}

Vector3 Vector3::operator*(const double scalar) {
    Vector3 result = Vector3(x * scalar, y * scalar, z * scalar);
    return result;
}

Vector3 Vector3::operator/(const double scalar) {
    Vector3 result = Vector3(x / scalar, y / scalar, z / scalar);
    return result;
}

ostream& operator<<(ostream& os, const Vector3 &vec) {
    os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
    
    return os;
}

double Vector3::getMagnitude() {
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::getNormalized() {
    return (*this) / getMagnitude();
}

double Vector3::dot(Vector3 vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(Vector3 vec) {
    Vector3 result = Vector3(y * vec.z - z * vec.y,
                             z * vec.x - x * vec.z,
                             x * vec.y - y * vec.x);
    return result;
}

double Vector3::projectScalar(Vector3 vec) {
    return dot(vec) / vec.getMagnitude(); // <a> * <b> / |b|
}

Vector3 Vector3::projectVector(Vector3 vec) {
    return vec * (dot(vec) / vec.dot(vec));
}

double Vector3::angle(Vector3 vec) {
    double cosine = dot(vec) / (getMagnitude() * vec.getMagnitude());
    return acos(cosine);
}

/**
 * Rotates this vector.
 *
 * <p>
 * The rotation matrix used (from [2]):<br>
 * <br>
 * [ cosA  -sinA  0  ][ cosB  0 sinB ][ 1   0      0  ][ x ]<br>
 * [ sinA  cosA   0  ][  0    1  0   ][ 0  cosY -sinY ][ y ]<br>
 * [ 0     0      1  ][ -sinB 0 cosB ][ 0  sinY  cosY ][ z ]<br>
 * <br>
 * whose yaw(around Z-axis), pitch(around Y-axis) and roll(around X-axis) angles are A(alpha), B(beta) and Y(gamma).<br>
 * WHY IS THE ROTATION MATRIX ABOVE NOT WORKING?????<br>
 * </p>
 *
 * <p>
 * For now, I'm rotating the vector around Z-axis, then Y-axis, then X-axis.
 * </p>
 *
 * <p>
 * Sources<br>
 * 1. http://stackoverflow.com/questions/5207708/rotation-in-a-vector2d-class-in-java<br>
 * 2. https://en.wikipedia.org/wiki/Rotation_matrix<br>
 * 3. http://mathworld.wolfram.com/RotationMatrix.html<br>
 * 4. http://www.iue.tuwien.ac.at/phd/wessner/node42.html<br>
 * 5. http://www.nh.cas.cz/people/lazar/celler/online_tools.php?start_vec=100,100,100&rot_ax=60,30,20&rot_ang=150
 * 6. https://docs.unity3d.com/ScriptReference/Transform.Rotate.html
 * <b>CAUTION: It alters the current vector.</b>
 * </p>
 *
 * @param  axis Axis of which this vector is to rotate around
 * @param  angle Amount of angle to rotate
 * @return No return value.
 */

void Vector3::rotate(Vector3 axis, double angle) {
    axis = axis.getNormalized();
    angle = angle * M_PI / 180.0;
    
    Matrix rotationMat = Matrix (3, 3, (double[]) {
        cos(angle) + axis.x*axis.x * (1 - cos(angle)), axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle), axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle),
        axis.y * axis.x * (1 - cos(angle)) + axis.z * sin(angle), cos(angle) + axis.y*axis.y * (1 - cos(angle)), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle),
        axis.z * axis.x * (1 - cos(angle)) - axis.y * sin(angle), axis.z * axis.y * (1 - cos(angle)) + axis.x * sin(angle), cos(angle) + axis.z*axis.z * (1 - cos(angle))});
    
    
    Matrix rotatedMat = rotationMat * (*this);
    
    x = rotatedMat.get(0, 0);
    y = rotatedMat.get(1, 0);
    z = rotatedMat.get(2, 0);
}