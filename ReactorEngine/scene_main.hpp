#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

class SceneMain : public Scene {
private:
    int carId;
    float clamp(float n, float lo, float hi);
    
public:
    SceneMain();
    
    void update();
    
};

#endif
