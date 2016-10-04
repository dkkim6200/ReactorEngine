#ifndef ENGINE_H
#define ENGINE_H

class Engine {
protected:
    std::chrono::high_resolution_clock::time_point previousTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    
    Renderer *renderer;
    
    string readFile(string fileName);
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    
public:
    Engine();
    
    GLuint scaleMatLoc;
    GLuint rotationMatLoc;
    GLuint translationMatLoc;
    
    void update();
};

#endif
