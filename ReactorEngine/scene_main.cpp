#include "main.hpp"
#include "scene_main.hpp"

SceneMain::SceneMain() : Scene() {
    //=====================================================================
    
    GameObject *gameObject1 = new GameObject();
    addGameObject(gameObject1);
    gameObject1->transform->setParent(NULL);
    gameObjectId1 = gameObject1->getId();
    
    gameObject1->transform->position = Vector3(0, 0, 5);
    gameObject1->transform->rotation = Quaternion::identity();
    gameObject1->transform->scale = Vector3(1, 1, 1) / 10;
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *arrowBlue = new GameObject(); // Y-axis
    addGameObject(arrowBlue);
    arrowBlue->transform->setParent(gameObject1->transform);
    
    arrowBlue->transform->position = Vector3(0, 0, 0);
    arrowBlue->transform->rotation = Quaternion(0, 0, 0);
    arrowBlue->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer2 = (Renderer *)arrowBlue->addComponent(COMPONENT_RENDERER);
    renderer2->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/textures/blue.bmp");
    
    //=====================================================================
    
    //=====================================================================
    
    GameObject *arrowGreen = new GameObject();
    addGameObject(arrowGreen);
    arrowGreen->transform->setParent(gameObject1->transform);
    
    arrowGreen->transform->position = Vector3(0, 0, 0);
    arrowGreen->transform->rotation = Quaternion(RAD(90), 0, 0);
    arrowGreen->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer3 = (Renderer *)arrowGreen->addComponent(COMPONENT_RENDERER);
    renderer3->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
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
    
    Renderer *renderer1 = (Renderer *)arrowRed->addComponent(COMPONENT_RENDERER);
    renderer1->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/arrow.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/arrow/textures/red.bmp");
    
    //=====================================================================
}

void SceneMain::update() {
    Scene::update();
    
    GameObject *gameObject1 = getGameObject(gameObjectId1);
    
    double rotation = RAD(90) * Time::deltaTime;
    
    cout << "====================\n\n" << endl;
    cout << "Position: " << gameObject1->transform->getWorldPosition() << endl;
    cout << "Rotation: " << DEG(gameObject1->transform->getWorldRotation().toEulerAngles()) << endl;
    cout << "Scale: " << gameObject1->transform->getWorldScale() << endl;
    
    cout << "Mouse: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")" << endl;
    cout << "Window: " << Window::width << "x" << Window::height << endl;
    
    // Test Transform::rotate(). See if the GameObject rotates without any gimbal lock.
    gameObject1->transform->rotation = Quaternion(glm::clamp(-Input::getMouseY(), -1.0, 1.0) * M_PI / 2, -Input::getMouseX() * M_PI / 2, 0);
}
