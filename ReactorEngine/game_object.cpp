#include "main.hpp"

GameObject::GameObject() {
    id = rand();
    
    transform = new Transform();
    components = new map<size_t, Component *>();
}

GameObject::~GameObject() {
    delete components;
}

int GameObject::getId() {
    return id;
}

//template <class T>
//T *GameObject::getComponent() {
//    if (typeid(T) == typeid(Transform)) {
//        return (T *)transform;
//    }
//    else if (hasComponent<T>()) {
//        return (T *)(components->at(typeid(T)));
//    } else {
//        return NULL;
//    }
//}
//
//template <class T>
//bool GameObject::hasComponent() {
//    return typeid(T) == typeid(Transform) || components->find(typeid(T)) != components->end();
//}
//
//template <class T>
//T *GameObject::addComponent() {
//    T *componentToAdd = new T();
//
//    if (!hasComponent<T>()) {
//        componentToAdd->gameObject = this;
//        components->emplace(typeid(T), componentToAdd);
//    } else {
//        delete componentToAdd;
//    }
//
//    return componentToAdd;
//}
