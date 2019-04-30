#include "main.hpp"
#include "scene_main.hpp"
#include <algorithm>

SceneMain::SceneMain() : Scene() {
    //=====================================================================
    
    GameObject *character = new GameObject();
    engine->addGameObject(character);
    characterId = character->getId();
    
    character->transform->position = Vector3(0, 0, 0);
    character->transform->rotation = Quaternion::identity();
    character->transform->scale = Vector3(1, 1, 1);
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *mainCamera = new GameObject();
    engine->addGameObject(mainCamera);
    mainCamera->transform->setParent(character->transform);
    
    mainCamera->transform->position = Vector3(0, 0, 0);
    mainCamera->transform->rotation = Quaternion::identity();
    mainCamera->transform->scale = Vector3(1, 1, 1);
    
    Camera *cameraComp = mainCamera->addComponent<Camera>();
    cameraComp->nearClipPlane = 0.1;
    cameraComp->farClipPlane = 100.0;
    cameraComp->fov = RAD(45.0);
    Camera::mainCamera = cameraComp;
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *mario = new GameObject();
    engine->addGameObject(mario);
    carId = mario->getId();
    
    mario->transform->position = Vector3(0, -0.5, -5);
    mario->transform->rotation = Quaternion(0, 0, 0);
    mario->transform->scale = Vector3(1, 1, 1);
    
    Renderer *rendererMario = mario->addComponent<Renderer>();
    rendererMario->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/maze/maze.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/maze/maze_texture.bmp");
    
    //=====================================================================
}

float SceneMain::clamp(float n, float lo, float hi) {
    return std::max(lo, std::min(n, hi));
}

void SceneMain::update() {
    Scene::update();
    
    if (Input::pressedKey == GLFW_KEY_Q) {
        exit(0);
    }
    
    GameObject *mainCamera = Camera::mainCamera->gameObject;
    mainCamera->transform->rotation = Quaternion(Vector3(1, 0, 0), clamp(-Input::getMouseY(), RAD(-90), RAD(90)));
    
    GameObject *character = engine->getGameObject(characterId);
    character->transform->rotation = Quaternion(Vector3(0, 1, 0), fmod(Input::getMouseX(), RAD(360)));
    
    cout << mainCamera->transform->right() << endl;
    
    if (Input::pressedKey == GLFW_KEY_W) {
        character->transform->translate(character->transform->forward() * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_S) {
        character->transform->translate(character->transform->forward() * -1 * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_A) {
        character->transform->translate(character->transform->right() * -1 * Time::deltaTime);
    }
    else if (Input::pressedKey == GLFW_KEY_D) {
        character->transform->translate(character->transform->right() * Time::deltaTime);
    }
    
    cout << "====================\n\n" << endl;
    cout << "Position: " << mainCamera->transform->position << endl;
    cout << "Forward vector: " << Vector3(1, 0, 0).rotate(mainCamera->transform->getWorldRotation()) << endl;
    cout << endl;
    cout << "Mouse: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")" << endl;
}
