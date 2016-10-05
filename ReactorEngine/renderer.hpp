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
    
    float **color;
    
    Renderer(Mesh *mesh);
    ~Renderer();
    
    void update(GLuint projectionMatLoc, GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc, GLuint colorVecLoc);
};

#endif
