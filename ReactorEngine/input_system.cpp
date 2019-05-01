#include "main.hpp"

InputSystem::InputSystem() {
}

InputSystem::~InputSystem() {
}

void InputSystem::start() {
    engine->eventBus->subscribe(this, &InputSystem::onKeyDown);
    engine->eventBus->subscribe(this, &InputSystem::onKeyUp);
}

void InputSystem::onKeyDown(KeyDownEvent *e) {
    Input::pressedKey = e->key;
}

void InputSystem::onKeyUp(KeyUpEvent *e) {
    Input::pressedKey = NULL;
}
