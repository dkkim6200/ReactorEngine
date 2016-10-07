#include "main.hpp"

Mesh::Mesh(char *objFilePath) {
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
    
    numVertices = tempVertexIndices.size();
    vertices = new Vector3[numVertices];
    
    numUVs = tempUVIndices.size();
    uvs = new Vector2[numUVs];
    
    numNormals = tempNormalIndices.size();
    normals = new Vector3[numNormals];
    
    for (int i = 0; i < tempVertexIndices.size(); i++) {
        vertices[i] = tempVertices[tempVertexIndices[i] - 1];
        uvs[i] = tempUVs[tempUVIndices[i] - 1];
        normals[i] = tempNormals[tempNormalIndices[i] - 1];
    }
}
