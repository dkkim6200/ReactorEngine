#ifndef EVENT_H
#define EVENT_H

/*
 Adopted from https://medium.com/@savas/nomad-game-engine-part-7-the-event-system-45a809ccb68f
 */

class System;

class Event {
public:
    virtual ~Event() { };
};

class EventHandlerBase {
public:
    virtual void call(Event *) = 0;
};

template <class T, class EventType>
class EventHandler : public EventHandlerBase {
private:
    typedef void (T::*MemberCallbackFunction)(EventType *);
    
    T *sys;
    MemberCallbackFunction callback;
    
public:
    EventHandler(T *system, MemberCallbackFunction callbackFunc) : sys {system}, callback {callbackFunc} { };
    
    void call(Event *e) {
        (sys->*callback)(static_cast<EventType *>(e));
    }
};

typedef std::list<EventHandlerBase *> EventHandlerList;

class EventBus {
private:
    std::unordered_map<TypeInfo, EventHandlerList *>subscribers;
    
public:
    template <class EventType>
    void publish(EventType *e) {
        EventHandlerList *eventHandlers = subscribers[TypeInfo::typeOf<EventType>()];
        
        if (eventHandlers == NULL) {
            return;
        }
        
        for (auto handler : *eventHandlers) {
            if (handler != NULL) {
                handler->call(e);
            }
        }
    }
    
    template <class T, class EventType>
    void subscribe(T *sys, void (T::*callback)(EventType *)) {
        EventHandlerList *eventHandlers = subscribers[TypeInfo::typeOf<EventType>()];
        
        if (eventHandlers == NULL) {
            eventHandlers = new EventHandlerList();
            subscribers[TypeInfo::typeOf<EventType>()] = eventHandlers;
        }
        
        eventHandlers->push_back(new EventHandler<T, EventType>(sys, callback));
    }
};

#endif
