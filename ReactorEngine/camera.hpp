#ifndef CAMERA_H
#define CAMERA_H

class Camera : public Component {
public:
    static Camera *mainCamera;
    
    double nearClipPlane;
    double farClipPlane;
    double fov;
    
    Camera();
};

#endif
