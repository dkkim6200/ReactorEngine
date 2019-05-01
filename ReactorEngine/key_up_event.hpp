#ifndef KEY_UP_EVENT_H
#define KEY_UP_EVENT_H

class Event;

class KeyUpEvent : public Event {
public:
    int key;
    
    KeyUpEvent(int _key) : key(_key) { };
    ~KeyUpEvent() { };
};


#endif
