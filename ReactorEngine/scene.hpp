#ifndef SCENE_H
#define SCENE_H

class Scene {
private:
    vector<System *> *systems;
    map<int, GameObject *> *gameObjects;
    
public:
    Scene();
    Scene(string fileName); // TODO!!
    
    virtual void update();
    
    GameObject *getGameObject(int id);
    void addGameObject(GameObject *gameObject);
};

#endif
