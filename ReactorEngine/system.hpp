#ifndef SYSTEM_HPP
#define SYSTEM_HPP

class System {
public:
    bool started;
    
    System() : started(false) { };
    virtual ~System();
    
    virtual void start() { };
    virtual void update() { };
};

#endif
