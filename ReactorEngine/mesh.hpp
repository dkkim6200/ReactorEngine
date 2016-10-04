#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    Vector3 *vertices;
    int numVertices;
    
    Mesh(Vector3 *vertices, int numVertices);
};

#endif
