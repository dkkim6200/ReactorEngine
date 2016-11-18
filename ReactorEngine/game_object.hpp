#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class GameObject {
private:
    int id;
    
    map<int, Component *> *components;
    
public:
    GameObject();
    virtual ~GameObject();
    
    int getId();
    Transform *transform;
    
    Component *getComponent(int id);
    Component *addComponent(int id);
};

#endif
