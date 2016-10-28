#include "main.hpp"

GameObject::GameObject() {
    id = rand();
    
    components = new map<int, Component *>();
    addComponent(COMPONENT_TRANSFORM);
    
    engine->addGameObject(this);
}

GameObject::~GameObject() {
    delete components;
}

int GameObject::getId() {
    return id;
}

Component *GameObject::getComponent(int id) {
    if (components->find(id) != components->end()) {
        return components->at(id);
    } else {
        return NULL;
    }
}

Component *GameObject::addComponent(int id) {
    Component *componentToAdd = NULL;
    
    if (id == COMPONENT_TRANSFORM) {
        componentToAdd = new Transform();
    }
    else if (id == COMPONENT_RENDERER) {
        componentToAdd = new Renderer();
    }
    else {
        cout << "NO SUCH COMPONENT!" << endl;
        exit(1);
    }
    
    if (components->find(componentToAdd->getId()) == components->end()) {
        componentToAdd->gameObject = this;
        components->emplace(componentToAdd->getId(), componentToAdd);
    }
    
    return componentToAdd;
}
