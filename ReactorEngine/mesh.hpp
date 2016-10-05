#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    Vector3 *vertices;
    int numVertices;
    
    int **patches;
    int numPatches;
    
    Mesh(Vector3 *vertices, int numVertices, int **patches, int numPatches);
};

#endif
