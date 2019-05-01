#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

class PlayerController : public Script {
private:
    float clamp(float n, float lo, float hi);
    
public:
    int cameraId;
    
    virtual void start();
    virtual void update();
};

#endif
