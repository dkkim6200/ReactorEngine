#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
private:
    int id;
    
    map<int, Component *> *components;
    map<int, GameObject *> *childGameObjects;
    
public:
    GameObject();
    virtual ~GameObject();
    
    int getId();
    
    Component *getComponent(int id);
    Component *addComponent(int id);
    
    
};

#endif
