#include "main.hpp"

Mesh::Mesh(Vector3 *vertices, int numVertices, int **patches, int numPatches) {
    this->vertices = vertices;
    this->numVertices = numVertices;
    
    this->patches = patches;
    this->numPatches = numPatches;
}
