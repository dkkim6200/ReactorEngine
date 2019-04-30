#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

class TimeSystem : public System {
private:
    std::chrono::high_resolution_clock::time_point previousTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    
public:
    TimeSystem();
    ~TimeSystem();
    
    virtual void update();
};

#endif
