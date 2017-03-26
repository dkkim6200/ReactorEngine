#include "main.hpp"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z) {
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

Vector3 Vector3::operator+=(const Vector3 &vec) {
    (*this) = (*this) + vec;
    return (*this);
}

Vector3 Vector3::operator-(const Vector3 &vec) {
    Vector3 result = Vector3(x - vec.x, y - vec.y, z - vec.z);
    return result;
}

Vector3 Vector3::operator-=(const Vector3 &vec) {
    (*this) = (*this) - vec;
    return (*this);
}

Vector3 Vector3::operator*(const float scalar) {
    Vector3 result = Vector3(x * scalar, y * scalar, z * scalar);
    return result;
}

Vector3 Vector3::operator/(const float scalar) {
    Vector3 result = Vector3(x / scalar, y / scalar, z / scalar);
    return result;
}

ostream& operator<<(ostream& os, const Vector3 &vec) {
    os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
    
    return os;
}

float Vector3::getMagnitude() {
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::getNormalized() {
    return (*this) / getMagnitude();
}

float Vector3::dot(Vector3 vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(Vector3 vec) {
    Vector3 result = Vector3(y * vec.z - z * vec.y,
                             z * vec.x - x * vec.z,
                             x * vec.y - y * vec.x);
    return result;
}

float Vector3::projectScalar(Vector3 vec) {
    return dot(vec) / vec.getMagnitude(); // <a> * <b> / |b|
}

Vector3 Vector3::projectVector(Vector3 vec) {
    return vec * (dot(vec) / vec.dot(vec));
}

float Vector3::angle(Vector3 vec) {
    float cosine = dot(vec) / (getMagnitude() * vec.getMagnitude());
    return acos(cosine);
}

void Vector3::rotate(Vector3 axis, float angle) {
    axis = axis.getNormalized();
    angle = angle * M_PI / 180.0;
    
    Matrix rotationMat = Matrix (3, 3, (float[]) {
        cos(angle) + axis.x*axis.x * (1 - cos(angle)), axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle), axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle),
        axis.y * axis.x * (1 - cos(angle)) + axis.z * sin(angle), cos(angle) + axis.y*axis.y * (1 - cos(angle)), axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle),
        axis.z * axis.x * (1 - cos(angle)) - axis.y * sin(angle), axis.z * axis.y * (1 - cos(angle)) + axis.x * sin(angle), cos(angle) + axis.z*axis.z * (1 - cos(angle))});
    
    
    Matrix rotatedMat = rotationMat * (*this);
    
    x = rotatedMat.get(0, 0);
    y = rotatedMat.get(1, 0);
    z = rotatedMat.get(2, 0);
}
