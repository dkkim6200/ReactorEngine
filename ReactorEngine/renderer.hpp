#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:
    Vector3 getBezierCurve(Vector3 *p, double t);
    Vector3 getBezierPatch(Vector3 *controlPoints, double u, double v);
    
public:
    GLuint vboId;
    GLuint iboId;
    
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
