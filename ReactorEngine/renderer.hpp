#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
public:
    GLuint vboId;
    Mesh *mesh;
    
    Vector3 scale;
    float rotation;
    Vector3 rotationAxis;
    Vector3 translation;
    
    Renderer(Mesh *mesh);
    ~Renderer();
    
    void update(GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc);
};

#endif
