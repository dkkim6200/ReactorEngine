#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    Vector3 *vertices;
    int numVertices;
    
    Vector2 *uvs;
    int numUVs;
    
    Vector3 *normals;
    int numNormals;
    
    Mesh(char *objFilePath);
};

#endif
