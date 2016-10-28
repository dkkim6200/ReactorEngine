#include "main.hpp"

bool Mesh::equals(float f1, float f2) {
    return fabs(f1 - f2) < 0.01f;
}

Mesh::Mesh(char *objFilePath, char *imagePath) {
    this->texture = new Texture(imagePath);
    
    std::vector<Vector3> tempVertices;
    std::vector<unsigned int> tempVertexIndices;
    
    std::vector<Vector2> tempUVs;
    std::vector<unsigned int> tempUVIndices;
    
    std::vector<Vector3> tempNormals;
    std::vector<unsigned int> tempNormalIndices;
    
    FILE *file = fopen(objFilePath, "r");
    if (file == NULL) {
        cout << "Error loading file: " << objFilePath << endl;
        exit(1);
    }
    
    while (true) {
        char strBuf[1000];
        
        int result = fscanf(file, "%s", strBuf);
        if (result == EOF) {
            break;
        }
        
        if (strcmp(strBuf, "v") == 0) {
            Vector3 vertex = Vector3(0, 0, 0);
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tempVertices.push_back(vertex);
        }
        else if (strcmp(strBuf, "vt") == 0) {
            Vector2 uv = Vector2(0, 0);
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            tempUVs.push_back(uv);
        }
        else if (strcmp(strBuf, "vn") == 0) {
            Vector3 normal = Vector3(0, 0, 0);
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tempNormals.push_back(normal);
        }
        else if (strcmp(strBuf, "f") == 0) {
            int vertexIndex[3];
            int uvIndex[3];
            int normalIndex[3];
            
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                cout << "File parsing error: " << objFilePath << endl;
                exit(1);
            }
            
            tempVertexIndices.push_back(vertexIndex[0]);
            tempVertexIndices.push_back(vertexIndex[1]);
            tempVertexIndices.push_back(vertexIndex[2]);
            tempUVIndices.push_back(uvIndex[0]);
            tempUVIndices.push_back(uvIndex[1]);
            tempUVIndices.push_back(uvIndex[2]);
            tempNormalIndices.push_back(uvIndex[0]);
            tempNormalIndices.push_back(uvIndex[1]);
            tempNormalIndices.push_back(uvIndex[2]);
        }
        else {
            // Unsignificant line; probably a comment
            fgets(strBuf, 1000, file);
        }
    }
    
    for (int i = 0; i < tempVertexIndices.size(); i++) {
//        vertices.push_back(tempVertices[tempVertexIndices[i] - 1]);
//        uvs.push_back(tempUVs[tempUVIndices[i] - 1]);
//        normals.push_back(tempNormals[tempNormalIndices[i] - 1]);
        
        int existingIndex = -1;
        for (int j = 0; j < vertices.size(); j++) {
            if (equals(tempVertices[tempVertexIndices[i] - 1].x, vertices[j].x) &&
                equals(tempVertices[tempVertexIndices[i] - 1].y, vertices[j].y) &&
                equals(tempVertices[tempVertexIndices[i] - 1].z, vertices[j].z) &&
                equals(tempUVs[tempUVIndices[i] - 1].x, uvs[j].x) &&
                equals(tempUVs[tempUVIndices[i] - 1].y, uvs[j].y) &&
                equals(tempNormals[tempNormalIndices[i] - 1].x, normals[j].x) &&
                equals(tempNormals[tempNormalIndices[i] - 1].y, normals[j].y) &&
                equals(tempNormals[tempNormalIndices[i] - 1].z, normals[j].z)) {
                
                existingIndex = j;
                
                break;
            }
        }
        
        if (existingIndex == -1) { // If the vertex with same UV and normal is not found
            vertices.push_back(tempVertices[tempVertexIndices[i] - 1]);
            uvs.push_back(tempUVs[tempUVIndices[i] - 1]);
            normals.push_back(tempNormals[tempNormalIndices[i] - 1]);
            indices.push_back(vertices.size() - 1);
        }
        else { // If the vertex already exists
            indices.push_back(existingIndex);
        }
    }
}
