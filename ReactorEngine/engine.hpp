#ifndef ENGINE_H
#define ENGINE_H

class Engine {
protected:
    std::chrono::high_resolution_clock::time_point previousTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    
    Vector3 *teapotVertices;
    int **teapotPatches;
    
    int numTeapotVertices;
    int numTeapotPatches;
    
    vector<System *> *systems;
    map<int, GameObject *> *gameObjects;
    
    string readFile(string fileName);
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    
public:
    GLuint transformationMatLoc;
    
    Engine();
    
    void update();
    
    GameObject *getGameObject(int id);
    void addGameObject(GameObject *gameObject);
};

#endif
