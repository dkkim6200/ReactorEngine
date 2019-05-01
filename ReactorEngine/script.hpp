#ifndef SCRIPT_H
#define SCRIPT_H

class System;

class Script : public Component, public System {
public:
    bool started;
    
    Script() : started(false) { };
    virtual ~Script();
};

#endif
