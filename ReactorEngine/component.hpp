#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
public:
    /**
     GameObject the current component is attached to.
     */
    GameObject *gameObject;
    
    Component();
    virtual ~Component();
};

#endif
