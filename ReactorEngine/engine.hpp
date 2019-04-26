#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    
    Scene *curScene;
    
public:
    GLuint transformationMatLoc;
    GLuint samplerLoc;
    
    GLuint shaderProgram;
    
    Engine();
    
    void loadScene(Scene *scene);
    
    void update();
    void onKeyPressed(int key);
    void onKeyRelease(int key);
    void onMouse(double x, double y);
};

#endif
