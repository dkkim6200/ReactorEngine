#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

class Engine;

class RenderSystem : public System {
private:
    void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType);
    void compileShaders();
    void initOpenGL();
    
    GLuint shaderProgram;
    GLuint transformationMatLoc;
    GLuint samplerLoc;
    
public:
    RenderSystem();
    ~RenderSystem();
    
    virtual void start();
    virtual void update();
};

#endif
