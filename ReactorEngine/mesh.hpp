#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
    std::vector<unsigned int> indices;
    
    Texture *texture;
    
    /**
     @brief Initializes Mesh object with OBJ file and a Texture with BMP image.
     
     @warning OBJ file must include vertices, texture coordinates (UVs), normal vertices, and faces.
     @warning Faces must be in format of "f xx/xx/xx xx/xx/xx xx/xx/xx".
     
     @param objFilePath Absolute path of OBJ file
     @param imagePath Absolute path of BMP file
     */
    Mesh(char *objFilePath, char *imagePath);
};

#endif
