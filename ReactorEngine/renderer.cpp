#include "main.hpp"

Renderer::Renderer() : Component(COMPONENT_RENDERER) {
    mesh = NULL;
    
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &uvboId);
    glGenBuffers(1, &iboId);
}

Renderer::~Renderer() {
    delete mesh;
}
