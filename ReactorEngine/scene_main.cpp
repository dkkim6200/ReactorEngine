#include "main.hpp"
#include "scene_main.hpp"

SceneMain::SceneMain() : Scene() {
    //=====================================================================
    
    GameObject *mainCamera = new GameObject();
    addGameObject(mainCamera);
    mainCamera->transform->setParent(NULL);
    
    mainCamera->transform->position = Vector3(0, 0, 0);
    mainCamera->transform->rotation = Quaternion::identity();
    mainCamera->transform->scale = Vector3(1, 1, 1);
    
    Camera *cameraComp = (Camera *)mainCamera->addComponent(COMPONENT_CAMERA);
    cameraComp->nearClipPlane = 0.1;
    cameraComp->farClipPlane = 1000;
    cameraComp->fov = RAD(30.0);
    Camera::mainCamera = cameraComp;
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *car1 = new GameObject();
    addGameObject(car1);
    car1->transform->setParent(mainCamera->transform);
    
    car1->transform->position = Vector3(0, -1, 0);
    car1->transform->rotation = Quaternion::identity();
    car1->transform->scale = Vector3(1, 1, 1) / 50;
    
    Renderer *rendererCar1 = (Renderer *)car1->addComponent(COMPONENT_RENDERER);
    rendererCar1->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/fire_truck_seperate_mesh.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehicle_Fire_Truck.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *car2 = new GameObject();
    addGameObject(car2);
    car2->transform->setParent(mainCamera->transform);
    
    car2->transform->position = Vector3(0, 1, 0);
    car2->transform->rotation = Quaternion::identity();
    car2->transform->scale = Vector3(1, 1, 1) / 50;
    
    Renderer *rendererCar2 = (Renderer *)car2->addComponent(COMPONENT_RENDERER);
    rendererCar2->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/fire_truck_seperate_mesh.obj",
                                  "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehicle_Fire_Truck.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *gameObject1 = new GameObject();
    addGameObject(gameObject1);
    //    gameObject1->transform->setParent(mainCamera->transform);
    gameObject1->transform->setParent(NULL);
    gameObject1Id = gameObject1->getId();
    
    gameObject1->transform->position = Vector3(0, 0, 1);
    gameObject1->transform->rotation = Quaternion::identity();
    gameObject1->transform->scale = Vector3(1, 1, 1) / 100;
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *arrowBlue = new GameObject(); // Y-axis
    addGameObject(arrowBlue);
    arrowBlue->transform->setParent(gameObject1->transform);
    
    arrowBlue->transform->position = Vector3(0, 0, 0);
    arrowBlue->transform->rotation = Quaternion(0, 0, 0);
    arrowBlue->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer1 = (Renderer *)arrowBlue->addComponent(COMPONENT_RENDERER);
    renderer1->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/textures/blue.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *arrowGreen = new GameObject();
    addGameObject(arrowGreen);
    arrowGreen->transform->setParent(gameObject1->transform);
    
    arrowGreen->transform->position = Vector3(0, 0, 0);
    arrowGreen->transform->rotation = Quaternion(RAD(90), 0, 0);
    arrowGreen->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer2 = (Renderer *)arrowGreen->addComponent(COMPONENT_RENDERER);
    renderer2->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/textures/green.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *arrowRed = new GameObject(); // X-axis
    addGameObject(arrowRed);
    arrowRed->transform->setParent(gameObject1->transform);
    
    //    arrowRed->transform->position = Vector3(0, 0, 0);
    arrowRed->transform->position = arrowBlue->transform->position.cross(arrowGreen->transform->position);
    arrowRed->transform->rotation = Quaternion(0, 0, -RAD(90));
    arrowRed->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer3 = (Renderer *)arrowRed->addComponent(COMPONENT_RENDERER);
    renderer3->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/textures/red.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *head = new GameObject();
    addGameObject(head);
    head->transform->setParent(NULL);
    
    head->transform->position = Vector3(0, 0, -1);
    head->transform->rotation = Quaternion::identity();
    head->transform->scale = Vector3(1, 1, 1) / 100;
    
    Renderer *headRenderer = (Renderer *)head->addComponent(COMPONENT_RENDERER);
    headRenderer->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/michael.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/michael.bmp");
    
    //=====================================================================
}

void SceneMain::update() {
    Scene::update();
    
    if (Input::pressedKey == 'q') {
        exit(0);
    }
    
    GameObject *world = getGameObject(worldId);
    GameObject *gameObject1 = getGameObject(gameObject1Id);
    GameObject *mainCamera = Camera::mainCamera->gameObject;
    
    Camera::mainCamera->gameObject->transform->rotation = Quaternion(0, -Input::getMouseX() * M_PI / 2, 0);
    //    Camera::mainCamera->gameObject->transform->rotation = Quaternion(glm::clamp(-Input::getMouseY(), -1.0, 1.0) * M_PI / 2, -Input::getMouseX() * M_PI / 2, 0);
    
    if (Input::pressedKey == 'w') {
        mainCamera->transform->translate((Camera::mainCamera->gameObject->transform->rotation.getConjugate() * Vector3(0, 0, 1).getQuaternion() * Camera::mainCamera->gameObject->transform->rotation).getVector() * Time::deltaTime);
    }
    else if (Input::pressedKey == 's') {
        mainCamera->transform->translate((Camera::mainCamera->gameObject->transform->rotation.getConjugate() * Vector3(0, 0, -1).getQuaternion() * Camera::mainCamera->gameObject->transform->rotation).getVector() * Time::deltaTime);
    }
    else if (Input::pressedKey == 'a') {
        mainCamera->transform->translate((Camera::mainCamera->gameObject->transform->rotation.getConjugate() * Vector3(-1, 0, 0).getQuaternion() * Camera::mainCamera->gameObject->transform->rotation).getVector() * Time::deltaTime);
    }
    else if (Input::pressedKey == 'd') {
        mainCamera->transform->translate((Camera::mainCamera->gameObject->transform->rotation.getConjugate() * Vector3(1, 0, 0).getQuaternion() * Camera::mainCamera->gameObject->transform->rotation).getVector() * Time::deltaTime);
    }
    
    cout << "====================\n\n" << endl;
    cout << "Position: " << gameObject1->transform->getWorldPosition() << endl;
    cout << "Rotation: " << DEG(gameObject1->transform->getWorldRotation().toEulerAngles()) << endl;
    cout << "Scale: " << gameObject1->transform->getWorldScale() << endl;
    cout << endl;
    cout << "Mouse: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")" << endl;
    cout << "Window: " << Window::width << "x" << Window::height << endl;
    cout << gameObject1->transform->getUp().cross(gameObject1->transform->getForward()) << endl;
}
