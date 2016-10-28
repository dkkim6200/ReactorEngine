#include "main.hpp"

Transform::Transform() : Component(COMPONENT_TRANSFORM) {
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1, 1, 1);
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) : Component(COMPONENT_TRANSFORM) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}
