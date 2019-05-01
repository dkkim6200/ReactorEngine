#ifndef INPUT_H
#define INPUT_H

class Engine;

class Input {
    friend class Engine;
    
private:
    static void init();
    
public:
    static int pressedKey;
    static double mouseX;
    static double mouseY;
    
    static int getKey();
    static double getMouseX();
    static double getMouseY();
};

#endif
