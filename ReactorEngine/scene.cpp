#include "main.hpp"

Scene::Scene() {
    systems = new vector<System *>();
    systems->push_back(new RenderSystem());
    
    gameObjects = new map<int, GameObject *>();
}

void Scene::update() {
    for (int i = 0; i < systems->size(); i++) {
        for (auto it = gameObjects->begin(); it != gameObjects->end(); it++) {
            systems->at(i)->update(it->second);
        }
    }
}

GameObject *Scene::getGameObject(int id) {
    if (gameObjects->find(id) != gameObjects->end()) {
        return gameObjects->at(id);
    }
    else {
        return NULL;
    }
}

void Scene::addGameObject(GameObject *gameObject) {
    gameObjects->emplace(gameObject->getId(), gameObject);
}
