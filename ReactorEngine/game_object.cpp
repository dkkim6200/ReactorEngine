#include "main.hpp"

GameObject::GameObject() {
    id = rand();
    
    transform = new Transform();
    components = new unordered_map<TypeInfo, Component *>();
    scripts = new unordered_map<TypeInfo, Script *>();
}

GameObject::~GameObject() {
    delete components;
}

int GameObject::getId() {
    return id;
}
