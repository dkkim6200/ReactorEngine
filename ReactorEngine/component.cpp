#include "main.hpp"

Component::Component(int id) {
    this->id = id;
}

Component::~Component() {
}

int Component::getId() {
    return id;
}
