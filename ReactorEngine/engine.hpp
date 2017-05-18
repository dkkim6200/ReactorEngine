#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    
    Scene *curScene;
    
public:
    GLuint transformationMatLoc;
    
    Engine();
    
    void loadScene(Scene *scene);
    
    void update();
    void onKeyPressed(int key);
    void onMouse(int x, int y);
};

#endif
