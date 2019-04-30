#ifndef SYSTEM_HPP
#define SYSTEM_HPP

class System {
public:
    virtual ~System();
    
    virtual void update() = 0;
};

#endif
