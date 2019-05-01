#ifndef KEY_DOWN_EVENT_H
#define KEY_DOWN_EVENT_H

class KeyDownEvent : public Event {
public:
    int key;
    
    KeyDownEvent(int _key) : key(_key) { };
    ~KeyDownEvent() { };
};

#endif
