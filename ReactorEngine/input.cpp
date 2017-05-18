#include "main.hpp"

int Input::pressedKey;
double Input::mouseX;
double Input::mouseY;

void Input::init() {
    pressedKey = -1;
    mouseX = 0;
    mouseY = 0;
}

bool Input::getKey(int glutKey) {
    return pressedKey;
}

double Input::getMouseX() {
    return mouseX;
}

double Input::getMouseY() {
    return mouseY;
}
