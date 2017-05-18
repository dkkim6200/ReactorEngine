#include "main.hpp"

std::chrono::high_resolution_clock::time_point Time::previousTime;
std::chrono::high_resolution_clock::time_point Time::currentTime;
double Time::deltaTime;

void Time::init() {
    previousTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0.0;
}

void Time::updateDeltaTime() {
    previousTime = currentTime;
    currentTime = std::chrono::high_resolution_clock::now();
    
    Time::deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
}
