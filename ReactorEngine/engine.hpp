#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    void initOpenGL();
    
    Scene *curScene;
    
    vector<System *> *systems;
    map<int, GameObject *> *gameObjects;
    
public:
    GLuint transformationMatLoc;
    GLuint samplerLoc;
    
    GLuint shaderProgram;
    
    Engine();
    
    void loadScene(Scene *scene);
    
    GameObject *getGameObject(int id);
    map<int, GameObject *> *getGameObjects();
    void addGameObject(GameObject *gameObject);
    
    void update();
    void onKeyPressed(int key);
    void onKeyRelease(int key);
    void onMouse(double x, double y);
};

#endif
