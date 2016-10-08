#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
public:
    GLuint vboId; // Vertex Buffer Object ID
    GLuint uvboId; // UV Buffer Object ID
    GLuint iboId;
    
    Mesh *mesh;
    
    Vector3 scale;
    float rotation;
    Vector3 rotationAxis;
    Vector3 translation;
    
    Renderer(Mesh *mesh);
    ~Renderer();
    
    void update(GLuint projectionMatLoc, GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc);
};

#endif
