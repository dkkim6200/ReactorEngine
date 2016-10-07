#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
public:
    GLuint vboId; // Vertex Buffer Object ID
    GLuint uvboId; // UV Buffer Object ID
    
    
    Mesh *mesh;
    Texture *texture;
    
    Vector3 scale;
    float rotation;
    Vector3 rotationAxis;
    Vector3 translation;
    
    Renderer(Mesh *mesh);
    ~Renderer();
    
    void update(GLuint projectionMatLoc, GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc, GLuint colorVecLoc);
};

#endif
