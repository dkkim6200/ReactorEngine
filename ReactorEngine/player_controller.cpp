#include "main.hpp"
#include "player_controller.hpp"

void PlayerController::start() {
    
}

void PlayerController::update() {
    if (Input::pressedKey == GLFW_KEY_Q) {
        exit(0);
    }
    
    GameObject *mainCamera = engine->getGameObject(cameraId);
    mainCamera->transform->rotation = Quaternion(Vector3(1, 0, 0), clamp(-Input::getMouseY(), RAD(-90), RAD(90)));
    
    gameObject->transform->rotation = Quaternion(Vector3(0, 1, 0), fmod(Input::getMouseX(), RAD(360)));
    
    if (Input::pressedKey == GLFW_KEY_W) {
        transform->translate(transform->forward() * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_S) {
        transform->translate(transform->forward() * -1 * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_A) {
        transform->translate(transform->right() * -1 * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_D) {
        transform->translate(transform->right() * Time::deltaTime);
    }
    
//    cout << "====================\n\n" << endl;
//    cout << "Position: " << mainCamera->transform->position << endl;
//    cout << "Forward vector: " << Vector3(1, 0, 0).rotate(mainCamera->transform->getWorldRotation()) << endl;
//    cout << endl;
//    cout << "Mouse: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")" << endl;
}

float PlayerController::clamp(float n, float lo, float hi) {
    return std::max(lo, std::min(n, hi));
}
