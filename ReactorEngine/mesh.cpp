#include "main.hpp"

bool equals(float f1, float f2) {
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
    
    ifstream file;
    file.open(objFilePath);
    string line;
    
    while (getline(file, line)) {
        if (line.length() == 0) {
            continue;
        }
        
        string lineType = line.substr(0, line.find(" "));
        string dataStr = line.substr(line.find(" "));
        
        stringstream stream(dataStr);
        
        if (lineType.compare("#") == 0) {
            continue;
        }
        else if (lineType.compare("v") == 0) {
            Vector3 vertex = Vector3(0, 0, 0);
            stream >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        }
        else if (lineType.compare("vt") == 0) {
            Vector2 uv = Vector2(0, 0);
            stream >> uv.x >> uv.y;
            tempUVs.push_back(uv);
        }
        else if (lineType.compare("vn") == 0) {
            Vector3 normal = Vector3(0, 0, 0);
            stream >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (lineType.compare("f") == 0) {
            bool matched = false;
            
            int vertexIndex[3];
            int uvIndex[3];
            int normalIndex[3];
            
            int matches = sscanf(dataStr.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
                                 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches == 9) {
                matched = true;
                
                tempVertexIndices.push_back(vertexIndex[0]);
                tempVertexIndices.push_back(vertexIndex[1]);
                tempVertexIndices.push_back(vertexIndex[2]);
                tempUVIndices.push_back(uvIndex[0]);
                tempUVIndices.push_back(uvIndex[1]);
                tempUVIndices.push_back(uvIndex[2]);
                tempNormalIndices.push_back(normalIndex[0]);
                tempNormalIndices.push_back(normalIndex[1]);
                tempNormalIndices.push_back(normalIndex[2]);
            }
            
            //=====================================================
            // Check if this set of indices is representing a quad.
            // If so, add another triangle to make it a quad.
            //=====================================================
            
            // There may be 4th index. Check for that.
            int extraVertexIndex;
            int extraUvIndex;
            int extraNormalIndex;
            
            // I really don't know how the hell this works. Shouldn't the fscanf above ready skipped a line???? How is the fscanf below sucessfully reading a line???
            matches = sscanf(dataStr.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                             &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                             &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                             &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                             &extraVertexIndex, &extraUvIndex, &extraNormalIndex);
            
            // If the 4th index does exist, this line represents a quad.
            if (matches == 12) {
                matched = true;
                
                // Create another triangle.
                tempVertexIndices.push_back(vertexIndex[2]);
                tempVertexIndices.push_back(extraVertexIndex);
                tempVertexIndices.push_back(vertexIndex[0]);
                tempUVIndices.push_back(uvIndex[2]);
                tempUVIndices.push_back(extraUvIndex);
                tempUVIndices.push_back(uvIndex[0]);
                tempNormalIndices.push_back(normalIndex[2]);
                tempNormalIndices.push_back(extraNormalIndex);
                tempNormalIndices.push_back(normalIndex[0]);
            }
            
            //=======================================================
            // Check if this set of indices represent a vertex texture coordinate index
            //=======================================================
            
            matches = sscanf(dataStr.c_str(), "%d/%d %d/%d %d/%d",
                             &vertexIndex[0], &uvIndex[0],
                             &vertexIndex[1], &uvIndex[1],
                             &vertexIndex[2], &uvIndex[2]);
            
            if (matches == 6) {
                matched = true;
                
                tempVertexIndices.push_back(vertexIndex[0]);
                tempVertexIndices.push_back(vertexIndex[1]);
                tempVertexIndices.push_back(vertexIndex[2]);
                tempUVIndices.push_back(uvIndex[0]);
                tempUVIndices.push_back(uvIndex[1]);
                tempUVIndices.push_back(uvIndex[2]);
                tempNormalIndices.push_back(1);
                tempNormalIndices.push_back(1);
                tempNormalIndices.push_back(1);
            }
            
            matches = sscanf(dataStr.c_str(), "%d/%d %d/%d %d/%d %d/%d",
                             &vertexIndex[0], &uvIndex[0],
                             &vertexIndex[1], &uvIndex[1],
                             &vertexIndex[2], &uvIndex[2],
                             &extraVertexIndex, &extraUvIndex);
            
            // If the 4th index does exist, this line represents a quad.
            if (matches == 8) {
                matched = true;
                
                // Create another triangle.
                tempVertexIndices.push_back(vertexIndex[2]);
                tempVertexIndices.push_back(extraVertexIndex);
                tempVertexIndices.push_back(vertexIndex[0]);
                tempUVIndices.push_back(uvIndex[2]);
                tempUVIndices.push_back(extraUvIndex);
                tempUVIndices.push_back(uvIndex[0]);
                tempNormalIndices.push_back(1);
                tempNormalIndices.push_back(1);
                tempNormalIndices.push_back(1);
            }
            
            //=======================================================
            // Check if this set of indices represent a vertex normal index
            //=======================================================
            
            matches = sscanf(dataStr.c_str(), "%d//%d %d//%d %d//%d",
                             &vertexIndex[0], &normalIndex[0],
                             &vertexIndex[1], &normalIndex[1],
                             &vertexIndex[2], &normalIndex[2]);
            
            if (matches == 6) {
                matched = true;
                
                tempVertexIndices.push_back(vertexIndex[0]);
                tempVertexIndices.push_back(vertexIndex[1]);
                tempVertexIndices.push_back(vertexIndex[2]);
                tempUVIndices.push_back(1);
                tempUVIndices.push_back(1);
                tempUVIndices.push_back(1);
                tempNormalIndices.push_back(normalIndex[0]);
                tempNormalIndices.push_back(normalIndex[1]);
                tempNormalIndices.push_back(normalIndex[2]);
            }
            
            matches = sscanf(dataStr.c_str(), "%d//%d %d//%d %d//%d %d//%d",
                             &vertexIndex[0], &normalIndex[0],
                             &vertexIndex[1], &normalIndex[1],
                             &vertexIndex[2], &normalIndex[2],
                             &extraVertexIndex, &extraNormalIndex);
            
            // If the 4th index does exist, this line represents a quad.
            if (matches == 8) {
                matched = true;
                
                // Create another triangle.
                tempVertexIndices.push_back(vertexIndex[2]);
                tempVertexIndices.push_back(extraVertexIndex);
                tempVertexIndices.push_back(vertexIndex[0]);
                tempUVIndices.push_back(1);
                tempUVIndices.push_back(1);
                tempUVIndices.push_back(1);
                tempNormalIndices.push_back(normalIndex[2]);
                tempNormalIndices.push_back(extraNormalIndex);
                tempNormalIndices.push_back(normalIndex[0]);
            }
            
            if (matched == false) {
                cout << "File parsing error: " << objFilePath << endl;
                exit(1);
            }
        }
    }
    
    file.close();
    
    if (tempUVIndices.size() == 0) {
        tempUVs.push_back(Vector2(0, 0));
    }
    
    if (tempNormals.size() == 0) {
        tempNormals.push_back(Vector3(0, 1, 0));
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
