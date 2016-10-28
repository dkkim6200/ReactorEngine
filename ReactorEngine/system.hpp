#ifndef SYSTEM_HPP
#define SYSTEM_HPP

class System {
public:
    virtual ~System();
    
    void update();
    virtual void update(GameObject *gameObject) = 0;
};

#endif
