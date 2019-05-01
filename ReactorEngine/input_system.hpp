#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

class KeyDownEvent;
class KeyUpEvent;

class InputSystem : public System {
public:
    InputSystem();
    ~InputSystem();
    
    virtual void start();
    virtual void onKeyDown(KeyDownEvent *e);
    virtual void onKeyUp(KeyUpEvent *e);
};

#endif /* input_system_hpp */
