#ifndef SCRIPT_H
#define SCRIPT_H

class Script : public Component {
public:
    virtual ~Script();
    
    virtual void start() = 0;
    virtual void update() = 0;
};

#endif
