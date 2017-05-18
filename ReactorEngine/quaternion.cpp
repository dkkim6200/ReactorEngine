#include "main.hpp"

Quaternion::Quaternion() : Quaternion(0, 0, 0, 1) {
}

Quaternion::Quaternion(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}


Quaternion::Quaternion(double xRot, double yRot, double zRot) {
    yRot *= -1;
    
    double cosHalfZ = cos(zRot * 0.5);
    double sinHalfZ = sin(zRot * 0.5);
    double cosHalfX = cos(xRot * 0.5);
    double sinHalfX = sin(xRot * 0.5);
    double cosHalfY = cos(yRot * 0.5);
    double sinHalfY = sin(yRot * 0.5);
    
    x = cosHalfZ * sinHalfX * cosHalfY + sinHalfZ * cosHalfX * sinHalfY;
    y = cosHalfZ * cosHalfX * sinHalfY - sinHalfZ * sinHalfX * cosHalfY;
    z = sinHalfZ * cosHalfX * cosHalfY - cosHalfZ * sinHalfX * sinHalfY;
    w = cosHalfZ * cosHalfX * cosHalfY + sinHalfZ * sinHalfX * sinHalfY;
}


Quaternion::Quaternion(Vector3 axis, double angle) {
    x = axis.x * sin(angle / 2);
    y = axis.y * sin(angle / 2);
    z = axis.z * sin(angle / 2);
    w = cos(angle / 2);
}

Quaternion Quaternion::identity() {
    return Quaternion(0, 0, 0, 1);
}

Quaternion Quaternion::operator*(const Vector3 vec) {
    const float w = - ((*this).x * vec.x) - ((*this).y * vec.y) - ((*this).z * vec.z);
    const float x =   ((*this).w * vec.x) + ((*this).y * vec.z) - ((*this).z * vec.y);
    const float y =   ((*this).w * vec.y) + ((*this).z * vec.x) - ((*this).x * vec.z);
    const float z =   ((*this).w * vec.z) + ((*this).x * vec.y) - ((*this).y * vec.x);
    
    return Quaternion(x, y, z, w);
}

Quaternion Quaternion::operator*(const Quaternion quat) {
    const float w = ((*this).w * quat.w) - ((*this).x * quat.x) - ((*this).y * quat.y) - ((*this).z * quat.z);
    const float x = ((*this).x * quat.w) + ((*this).w * quat.x) + ((*this).y * quat.z) - ((*this).z * quat.y);
    const float y = ((*this).y * quat.w) + ((*this).w * quat.y) + ((*this).z * quat.x) - ((*this).x * quat.z);
    const float z = ((*this).z * quat.w) + ((*this).w * quat.z) + ((*this).x * quat.y) - ((*this).y * quat.x);
    
    return Quaternion(x, y, z, w);
}

ostream& operator<<(ostream& os, const Quaternion &q) {
    os << "<" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ">";
    
    return os;
}

Vector3 Quaternion::getVector() {
    return Vector3(x, y, z);
}

void Quaternion::normalize() {
    double magnitude = sqrt(x * x + y * y + z * z + w * w);
    
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
}

Quaternion Quaternion::getConjugate() {
    return Quaternion(-x, -y, -z, w);
}

Vector3 Quaternion::toEulerAngles() {
    // roll (x-axis rotation)
    double t0 = +2.0 * (w * x + y * z);
    double t1 = +1.0 - 2.0 * (x * x + y * y);
    double roll = std::atan2(t0, t1);

    // pitch (y-axis rotation)
    double t2 = +2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    double pitch = std::asin(t2);

    // yaw (z-axis rotation)
    double t3 = +2.0 * (w * z + x * y);
    double t4 = +1.0 - 2.0 * (y * y + z * z);
    double yaw = std::atan2(t3, t4);
    
    return Vector3(roll, pitch, yaw);
}
