#include "main.hpp"

TimeSystem::TimeSystem() {
    previousTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    Time::deltaTime = 0.0;
}

TimeSystem::~TimeSystem() {
}

void TimeSystem::update() {
    previousTime = currentTime;
    currentTime = std::chrono::high_resolution_clock::now();
    
    Time::deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
    
    if (SHOW_FPS) {
        cout << 1.0 / Time::deltaTime << " FPS" << endl;
    }
}
