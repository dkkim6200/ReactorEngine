#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
protected:
    int id;
    
public:
    GameObject *gameObject;
    
    Component(int id);
    virtual ~Component();
    
    int getId();
};

#endif
