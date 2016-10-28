#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer : public Component {
public:
    GLuint vboId; // Vertex Buffer Object ID
    GLuint uvboId; // UV Buffer Object ID
    GLuint iboId;
    
    Mesh *mesh;
    
    Renderer();
    ~Renderer();
};

#endif
