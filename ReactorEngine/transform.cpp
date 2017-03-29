#include "main.hpp"

Transform::Transform() : Component(COMPONENT_TRANSFORM) {
    parent = NULL;
    children = new vector<Transform *>();
    
    position = Vector3(0, 0, 0);
    rotation = Quaternion(0, 0, 0, 0);
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
    if (parent == NULL) {
        return position;
    }
    else {
        return parent->getWorldPosition() + position;
    }
}

Quaternion Transform::getWorldRotation() {
    if (parent == NULL) {
        return rotation;
    }
    else {
        return parent->rotation * rotation;
    }
}

Vector3 Transform::getWorldScale() {
    if (parent == NULL) {
        return scale;
    }
    else {
        Vector3 parentScale = parent->getWorldScale();
        return Vector3(parentScale.x * scale.x, parentScale.y * scale.y, parentScale.z * scale.z);
    }
}

void Transform::translate(Vector3 translation) {
    position += translation;
}

void Transform::rotate(Vector3 eulerAngles) {
    rotation = Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z) * rotation;
}

void Transform::rotate(Vector3 axis, double angle) {
    rotation = Quaternion(axis, angle) * rotation;
}
