#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;
class Transform;
class Engine;

class Component {
    friend class Engine;
    
private:
    TypeInfo type;
    
public:
    /**
     GameObject the current component is attached to.
     */
    GameObject *gameObject;
    Transform *transform;
    
    Component();
    virtual ~Component();
};

#endif
