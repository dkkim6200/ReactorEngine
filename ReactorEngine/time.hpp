#ifndef TIME_H
#define TIME_H

class Time {
private:
    static std::chrono::high_resolution_clock::time_point previousTime;
    static std::chrono::high_resolution_clock::time_point currentTime;
    
public:
    static double deltaTime;
    
    static void init();
    static void updateDeltaTime();
};

#endif
