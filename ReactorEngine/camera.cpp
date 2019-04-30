#include "main.hpp"

Camera *Camera::mainCamera;

Camera::Camera() {
    this->nearClipPlane = 0;
    this->farClipPlane = 0;
    this->fov = 0;
}
