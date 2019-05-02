#include "main.hpp"
#include <unistd.h>

Engine::Engine() {
    // Reactor Engine initialization
    
    curScene = NULL;
    
    Input::init();
    
    gameObjects = new unordered_map<int, GameObject *>();
    
    componentContainers = new unordered_map<TypeInfo, vector<Component *> *>();
    scriptContainers = new unordered_map<TypeInfo, vector<Script *> *>();
    scripts = new vector<Script *>();
    
    systems = new vector<System *>();
    systems->push_back(new RenderSystem());
    systems->push_back(new TimeSystem());
    systems->push_back(new ScriptSystem());
    systems->push_back(new InputSystem());
    
    eventBus = new EventBus();
}

void Engine::ignite() {
    for (int i = 0; i < systems->size(); i++) {
        systems->at(i)->start();
    }
}

void Engine::update() {
    for (int i = 0; i < systems->size(); i++) {
        systems->at(i)->update();
    }
    
    if (1.0 / Time::deltaTime > MAX_FPS) {
        usleep(500000.0 * (1.0 / MAX_FPS - Time::deltaTime));
    }
}

void Engine::loadScene(Scene *scene) {
    curScene = scene;
}

GameObject *Engine::getGameObject(int id) {
    if (gameObjects->find(id) != gameObjects->end()) {
        return gameObjects->at(id);
    }
    else {
        return NULL;
    }
}

void Engine::addGameObject(GameObject *gameObject) {
    (*gameObjects)[gameObject->getId()] = gameObject;
}

void Engine::removeComponent(Component *component) {
    if (dynamic_cast<Script *>(component)) {
        vector<Script *> *curContainer = (*scriptContainers)[component->type];
        
        curContainer->erase(std::remove(curContainer->begin(), curContainer->end(), (Script *)component));
    }
    else {
        vector<Component *> *curContainer = (*componentContainers)[component->type];
        
        curContainer->erase(std::remove(curContainer->begin(), curContainer->end(), component));
    }
}

void Engine::onMouse(double x, double y) {
//    Input::mouseX = (x - (Window::width / 2)) / (Window::width / 2);
//    Input::mouseY = (y - (Window::height / 2)) / (Window::height / 2);
    
    Input::mouseX = (x / INIT_SCREEN_WIDTH) - 0.5;
    Input::mouseY = -((y / INIT_SCREEN_HEIGHT) - 0.5);
}
