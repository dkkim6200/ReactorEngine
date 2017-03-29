#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer : public Component {
public:
    /**
     @brief Vertex Buffer Object ID
     */
    GLuint vboId;
    
    /**
     @brief UV Buffer Object ID
     */
    GLuint uvboId;
    
    /**
     @brief Index Buffer Object ID
     */
    GLuint iboId;
    
    /**
     @brief The 3D mesh that the renderer shall be reponsible for rendering.
     */
    Mesh *mesh;
    
    /**
     @brief Initiates a new renderer object with no mesh
     */
    Renderer();
    
    ~Renderer();
};

#endif
