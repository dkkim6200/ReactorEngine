#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
private:
    int id;
    
    map<size_t, Component *> *components;
    
public:
    GameObject();
    virtual ~GameObject();
    
    int getId();
    Transform *transform;
    
    // The template functions have to be in the header file.
    // TODO: find a solution to put the function definitions to the CPP file.
    
    template <class T>
    T *getComponent() {
        if (typeid(T).hash_code() == typeid(Transform).hash_code()) {
            return (T *)transform;
        }
        else if (hasComponent<T>()) {
            return (T *)(components->at(typeid(T).hash_code()));
        } else {
            return NULL;
        }
    }
    
    template <class T>
    bool hasComponent() {
        return typeid(T).hash_code() == typeid(Transform).hash_code() || components->find(typeid(T).hash_code()) != components->end();
    }
    
    template <class T>
    T *addComponent() {
        T *componentToAdd = new T();
        
        if (!this->hasComponent<T>()) {
            componentToAdd->gameObject = this;
            components->emplace(typeid(T).hash_code(), componentToAdd);
        } else {
            delete componentToAdd;
        }
        
        return componentToAdd;
    }
};

#endif
