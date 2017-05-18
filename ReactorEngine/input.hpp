#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    static int pressedKey;
    static double mouseX;
    static double mouseY;
    
    static void init();
    
    static bool getKey(int glutKey);
    static double getMouseX();
    static double getMouseY();
};

#endif
