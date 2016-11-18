#include "main.hpp"

GameObject::GameObject() {
    id = rand();
    
    transform = new Transform();
    components = new map<int, Component *>();
}

GameObject::~GameObject() {
    delete components;
}

int GameObject::getId() {
    return id;
}

Component *GameObject::getComponent(int id) {
    if (id == COMPONENT_TRANSFORM) {
        return transform;
    }
    else if (components->find(id) != components->end()) {
        return components->at(id);
    } else {
        return NULL;
    }
}

Component *GameObject::addComponent(int id) {
    Component *componentToAdd = NULL;
    
    if (id == COMPONENT_RENDERER) {
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
