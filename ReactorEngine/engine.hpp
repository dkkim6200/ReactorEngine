#ifndef ENGINE_H
#define ENGINE_H

class RenderSystem;
class TimeSystem;
class ScriptSystem;
struct TypeInfo;
class EventBus;

class Engine {
    friend class RenderSystem;
    friend class TimeSystem;
    friend class ScriptSystem;
    friend class GameObject;
    
private:
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    void initOpenGL();
    
    Scene *curScene;
    
    vector<System *> *systems;
    unordered_map<int, GameObject *> *gameObjects;
    unordered_map<TypeInfo, vector<Component *> *> *componentContainers;
    unordered_map<TypeInfo, vector<Script *> *> *scriptContainers;
    vector<Script *> *scripts;

    GLuint transformationMatLoc;
    GLuint samplerLoc;
    
    GLuint shaderProgram;
    
    void removeComponent(Component *component);
    
    template <class T>
    T *createComponent() {
        T *componentToAdd = new T();
        componentToAdd->type = TypeInfo::typeOf<T>();
        
        if (dynamic_cast<Script *>(componentToAdd)) {
            if (scriptContainers->find(componentToAdd->type) == scriptContainers->end()) {
                (*scriptContainers)[componentToAdd->type] = new vector<Script *>();
            }
            
            (*scriptContainers)[componentToAdd->type]->push_back((Script *)componentToAdd);
            scripts->push_back((Script *)componentToAdd);
        }
        else {
            if (componentContainers->find(componentToAdd->type) == componentContainers->end()) {
                (*componentContainers)[componentToAdd->type] = new vector<Component *>();
            }
            
            (*componentContainers)[componentToAdd->type]->push_back((Component *)componentToAdd);
        }
        
        return componentToAdd;
    }
    
    template <class T>
    vector<T*> *getComponents() {
        TypeInfo type = TypeInfo::typeOf<T>();
        
        if( dynamic_cast<Script *>( &(T()) )) {
            return (*scriptContainers)[type];
        }
        
        return (vector<T*> *)(*componentContainers)[type];
    }
    
public:
    EventBus *eventBus;
    
    Engine();
    
    void onKeyPressed(int key);
    void onKeyRelease(int key);
    void onMouse(double x, double y);
    
    void ignite();
    void update();
    
    void loadScene(Scene *scene);
    
    GameObject *getGameObject(int id);
    void addGameObject(GameObject *gameObject);
};

#endif
