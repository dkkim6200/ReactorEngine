#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
private:
    bool equals(float f1, float f2);
    
public:
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
    std::vector<unsigned int> indices;
    
    Texture *texture;
    
    Mesh(char *objFilePath, char *imagePath);
};

#endif
