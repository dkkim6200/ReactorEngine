#include "main.hpp"

Transform::Transform() : Component(COMPONENT_TRANSFORM) {
    parent = NULL;
    children = new vector<Transform *>();
    
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1, 1, 1);
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) : Component(COMPONENT_TRANSFORM) {
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
    Matrix rotationMat = Matrix::getRotationMat(Vector3(0, 0, 1), rotation.z);
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

// TODO: make Transform::getWorldRotation()
