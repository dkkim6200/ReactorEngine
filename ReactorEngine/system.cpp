#include "main.hpp"

System::~System() {
}

void System::update() {
    for (auto it = engine->gameObjects->begin(); it != engine->gameObjects->end(); it++) {
        GameObject *curGameObject = it->second;
        
        update(curGameObject);
    }
}
