#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

class SceneMain : public Scene {
private:
    int gameObject1Id;
    int worldId;
    
public:
    SceneMain();
    
    void update();
    
};

#endif
