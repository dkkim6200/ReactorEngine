#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
    friend class RenderSystem;
    friend class ScriptSystem;
    
private:
    int id;
    
    unordered_map<TypeInfo, Component *> *components;
    unordered_map<TypeInfo, Script *> *scripts;
    
public:
    GameObject();
    virtual ~GameObject();
    
    int getId();
    Transform *transform;
    
    template <class T>
    T *getComponent() {
        TypeInfo type = TypeInfo::typeOf<T>();
        
        if (type == TypeInfo::typeOf<Transform>()) {
            return (T *)transform;
        }
        else if (hasScript<T>()) {
            return (T *)(scripts->at(type));
        }
        else if (hasComponent<T>()) {
            return (T *)(components->at(type));
        } else {
            return NULL;
        }
    }
    
    template <class T>
    bool hasComponent() {
        TypeInfo type = TypeInfo::typeOf<T>();
        
        return type == TypeInfo::typeOf<Transform>() || components->find(type) != components->end() || hasScript<T>();
    }
    
    template <class T>
    bool hasScript() {
        TypeInfo type = TypeInfo::typeOf<T>();
        
        return std::is_base_of<Script, T>::value && scripts->find(type) != scripts->end();
    }
    
    template <class T>
    T *addComponent() {
        T *componentToAdd = engine->createComponent<T>();
        componentToAdd->gameObject = this;
        componentToAdd->transform = this->transform;
        
        TypeInfo type = TypeInfo::typeOf<T>();
        
        if ((std::is_base_of<Script, T>::value) && scripts->find(type) == scripts->end()) {
            scripts->emplace(type, (Script *)componentToAdd);
        }
        else if (!this->hasComponent<T>()) {
            components->emplace(type, (Component *)componentToAdd);
        } else {
            delete componentToAdd;
        }
        
        return componentToAdd;
    }
    
    template <class T>
    void removeComponent() {
        T *componentToRemove = getComponent<T>();
        
        engine->removeComponent(componentToRemove);
        delete componentToRemove;
    }
};

#endif
