#include "main.hpp"

Renderer::Renderer() {
    mesh = NULL;
    
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &uvboId);
    glGenBuffers(1, &iboId);
}

Renderer::~Renderer() {
    delete mesh;
}
