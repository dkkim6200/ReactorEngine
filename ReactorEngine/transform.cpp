#include "main.hpp"

Transform::Transform() : Component(COMPONENT_TRANSFORM) {
    parent = NULL;
    children = new vector<Transform *>();
    
    position = Vector3(0, 0, 0);
    rotation = Quaternion::identity();
    scale = Vector3(1, 1, 1);
}

Transform::Transform(Vector3 position, Quaternion rotation, Vector3 scale) : Component(COMPONENT_TRANSFORM) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Transform *Transform::getParent() {
    return parent;
}

void Transform::setParent(Transform *parent) {
    if (this->parent != NULL) {
        auto position = find(this->parent->children->begin(), this->parent->children->end(), this);
        this->parent->children->erase(position);
    }
    
    this->parent = parent;
    
    if (this->parent != NULL) {
        this->parent->children->push_back(this);
    }
}

Matrix Transform::getTransformationMat() {
    Matrix scaleMat = Matrix::getScaleMat(scale);
    Matrix rotationMat = Matrix::getRotationMat(rotation);
    Matrix translationMat = Matrix::getTranslationMat(position);
    
    return translationMat * rotationMat * scaleMat;
}

Matrix Transform::getWorldTransformationMat() {
    if (parent == NULL) {
        return getTransformationMat();
    }
    else {
        return parent->getWorldTransformationMat() * getTransformationMat();
    }
}

Vector3 Transform::getWorldPosition() {
    Matrix worldTransformMat = getWorldTransformationMat();
    
    return Vector3(worldTransformMat.get(0, 3), worldTransformMat.get(1, 3), worldTransformMat.get(2, 3));
}

Quaternion Transform::getWorldRotation() {
//    Matrix worldTransformMat = getWorldTransformationMat();
//    Vector3 worldScale = getWorldScale();
//    
//    Matrix rotationMat = Matrix(4, 4, (float[]) {
//        worldTransformMat.get(0, 0) / scale.x, worldTransformMat.get(0, 1) / scale.y, worldTransformMat.get(0, 2) / scale.z, 0,
//        worldTransformMat.get(1, 0) / scale.x, worldTransformMat.get(1, 1) / scale.y, worldTransformMat.get(1, 2) / scale.z, 0,
//        worldTransformMat.get(2, 0) / scale.x, worldTransformMat.get(2, 1) / scale.y, worldTransformMat.get(2, 2) / scale.z, 0,
//        0,                                     0,                                     0,                                     1
//    });
//    
//    Quaternion result = Quaternion::identity();
//    result.w = sqrt(1.0 + rotationMat.get(0, 0) + rotationMat.get(1, 1) + rotationMat.get(2, 2)) / 2.0;
//    double w4 = 4.0 * result.w;
//    result.x = (rotationMat.get(2, 1) - rotationMat.get(1, 2)) / w4;
//    result.y = (rotationMat.get(0, 2) - rotationMat.get(2, 0)) / w4;
//    result.z = (rotationMat.get(1, 0) - rotationMat.get(0, 1)) / w4;
//    
//    return result;
    
    if (parent == NULL) {
        return rotation;
    }
    else {
        return rotation * parent->getWorldRotation();
    }
}

Vector3 Transform::getWorldScale() {
//    Matrix worldTransformMat = getWorldTransformationMat();
//    
//    double scaleX = Vector3(worldTransformMat.get(0, 0), worldTransformMat.get(1, 0), worldTransformMat.get(2, 0)).getMagnitude();
//    double scaleY = Vector3(worldTransformMat.get(0, 1), worldTransformMat.get(1, 1), worldTransformMat.get(2, 1)).getMagnitude();
//    double scaleZ = Vector3(worldTransformMat.get(0, 2), worldTransformMat.get(1, 2), worldTransformMat.get(2, 2)).getMagnitude();
//    
//    return Vector3(scaleX, scaleY, scaleZ);
    
    if (parent == NULL) {
        return scale;
    }
    else {
        Vector3 parentScale = parent->getWorldScale();
        return Vector3(parentScale.x * scale.x, parentScale.y * scale.y, parentScale.z * scale.z);
    }
}

Vector3 Transform::getUp() {
    Quaternion worldRot = getWorldRotation();
    return (worldRot.getConjugate() * Vector3(0, 1, 0).getQuaternion() * worldRot).getVector();
}

Vector3 Transform::getForward() {
    Quaternion worldRot = getWorldRotation();
    return (worldRot.getConjugate() * Vector3(0, 0, -1).getQuaternion() * worldRot).getVector();
}

Vector3 Transform::getRight() {
    Quaternion worldRot = getWorldRotation();
    return (worldRot.getConjugate() * Vector3(1, 0, 0).getQuaternion() * worldRot).getVector();
}

void Transform::translate(Vector3 translation) {
    position += translation;
}

void Transform::rotate(Vector3 eulerAngles) {
    rotation = rotation * Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
    
//    rotation = rotation * Quaternion(eulerAngles.x, 0, 0);
//    rotation = rotation * Quaternion(0, eulerAngles.y, 0);
//    rotation = Quaternion(0, 0, eulerAngles.z) * rotation;
}

void Transform::rotate(Vector3 axis, double angle) {
    rotation = Quaternion(axis, angle) * rotation;
}
