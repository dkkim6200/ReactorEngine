#include "main.hpp"
#include "scene_main.hpp"
#include "player_controller.hpp"

#include <algorithm>

SceneMain::SceneMain() : Scene() {
    //=====================================================================
    
    GameObject *character = new GameObject();
    engine->addGameObject(character);
    
    character->transform->position = Vector3(0, 0, 0);
    character->transform->rotation = Quaternion::identity();
    character->transform->scale = Vector3(1, 1, 1);
    
    GameObject *mainCamera = new GameObject();
    engine->addGameObject(mainCamera);
    mainCamera->transform->setParent(character->transform);
    
    mainCamera->transform->position = Vector3(0, 0, 0);
    mainCamera->transform->rotation = Quaternion::identity();
    mainCamera->transform->scale = Vector3(1, 1, 1);
    
    //=====================================================================
    
    PlayerController *playerController = character->addComponent<PlayerController>();
    playerController->cameraId = mainCamera->getId();
    
    //=====================================================================
    
    Camera *cameraComp = mainCamera->addComponent<Camera>();
    cameraComp->nearClipPlane = 0.1;
    cameraComp->farClipPlane = 100.0;
    cameraComp->fov = RAD(45.0);
    Camera::mainCamera = cameraComp;
    
    //=====================================================================
    
    GameObject *floor = new GameObject();
    engine->addGameObject(floor);
    floor->transform->position = Vector3(0, -2.25, 0);
    floor->transform->rotation = Quaternion::identity();
    floor->transform->scale = Vector3(10, 0.5, 10);

    Renderer *floorRenderer = floor->addComponent<Renderer>();
    floorRenderer->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/floor/floor.obj",
                                   "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/floor/floor.bmp");
}
