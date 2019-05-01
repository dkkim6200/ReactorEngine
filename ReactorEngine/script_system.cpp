#include "main.hpp"

ScriptSystem::ScriptSystem() {
}

ScriptSystem::~ScriptSystem() {
}

void ScriptSystem::update() {
    vector<Script *> *scripts = engine->scripts;
    
    for (auto it_script = engine->scripts->begin(); it_script != engine->scripts->end(); it_script++) {
       (*it_script)->update();
    }
}
