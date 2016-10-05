#include "main.hpp"

Renderer::Renderer(Mesh *mesh){
    this->mesh = mesh;
    
    rotation = 0.0f;
    rotationAxis = Vector3(1.0f, 1.0f, 0.0f);
    scale = Vector3(0.3f, 0.3f, 0.3f);
    translation = Vector3(0.0f, 0.0f, 5.0f);
    
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vector3), mesh->vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &iboId);
    
    color = new float*[mesh->numPatches];
    for (int i = 0; i < mesh->numPatches; i++) {
        color[i] = new float[3];
        color[i][0] = (float)rand() / INT_MAX;
        color[i][1] = (float)rand() / INT_MAX;
        color[i][2] = (float)rand() / INT_MAX;
    }
}

Renderer::~Renderer() {
    delete mesh;
}

void Renderer::update(GLuint projectionMatLoc, GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc, GLuint colorVecLoc) { // Render mesh
    
    rotation += 90 * Time::deltaTime;
    rotation = fmod(rotation, 360.0f);
    
    //================================================================
    // Update Matrices
    //================================================================
    
    Matrix projectionMat = Matrix::getProjectionMat((float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f, 30.0f * M_PI / 180.0f);
    
    // orthogonal projection
//    projectionMat = Matrix(4, 4, (float[]) {
//        1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 0, 0,
//        0, 0, 0, 1
//    });
    
    glUniformMatrix4fv(projectionMatLoc, 1, true, projectionMat.m);
    
    Matrix scaleMat = Matrix::getScaleMat(scale);
    glUniformMatrix4fv(scaleMatLoc, 1, true, scaleMat.m);
    
    Matrix rotationMat = Matrix::getRotationMat(rotationAxis, rotation * M_PI / 180.0f);
    glUniformMatrix4fv(rotationMatLoc, 1, true, rotationMat.m);
    
    Matrix translationMat = Matrix::getTranslationMat(translation);
    glUniformMatrix4fv(translationMatLoc, 1, true, translationMat.m);
    
    //=================================================================
    // Calculate Bezier Patches
    //=================================================================
    
    int divs = 16; // Must be >= 16
    
    Vector3 *controlPoints = new Vector3[divs];
    Vector3 *resultVertices = new Vector3[(divs + 1) * (divs + 1)];
    int *vertexIndex = new int[divs * divs * 6]; // 2 Triangles = 6 Verices
    
    for (int i = 0; i < mesh->numPatches; i++) { // numTeapotPatches
        for (int j = 0; j < NUM_VERTICES_PER_PATCH; j++) {
            controlPoints[j] = mesh->vertices[mesh->patches[i][j] - 1];
        }
        
        for (int j = 0, k = 0; j < divs + 1; j++) {
            for (int l = 0; l < divs + 1; l++, k++) {
                resultVertices[k] = getBezierPatch(controlPoints, l / (double)divs, j / (double)divs);
            }
        }
        
        for (int j = 0, k = 0; j < divs; j++) {
            for (int l = 0; l < divs; l++, k++) {
                vertexIndex[k * 6] = (divs + 1) * j + l;
                vertexIndex[k * 6 + 1] = (divs + 1) * (j + 1) + l;
                vertexIndex[k * 6 + 2] = (divs + 1) * (j + 1) + l + 1;
                
                vertexIndex[k * 6 + 3] = (divs + 1) * j + l;
                vertexIndex[k * 6 + 4] = (divs + 1) * (j + 1) + l + 1;
                vertexIndex[k * 6 + 5] = (divs + 1) * j + l + 1;
            }
        }
        
        //================================================================
        // Render each patches
        //================================================================
        
        glUniform3fv(colorVecLoc, 1, color[i]);
        
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, (divs + 1) * (divs + 1) * sizeof(Vector3), resultVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, divs * divs * 6 * sizeof(int), vertexIndex, GL_STATIC_DRAW);
        
        glDrawElements(GL_TRIANGLES, divs * divs * 6, GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(0);
    }
    
    delete [] controlPoints;
    delete [] resultVertices;
    delete [] vertexIndex;
}

Vector3 Renderer::getBezierCurve(Vector3 *p, double t) {
    // compute coefficients
    double k1 = (1 - t) * (1 - t) * (1 - t);
    double k2 = 3 * (1 - t) * (1 - t) * t;
    double k3 = 3 * (1 - t) * t * t;
    double k4 = t * t * t;
    
    // weight the four control points using coefficients
    return p[0] * k1 + p[1] * k2 + p[2] * k3 + p[3] * k4;
}

Vector3 Renderer::getBezierPatch(Vector3 *controlPoints, double u, double v) {
    Vector3 uCurve[4];
    
    for (int i = 0; i < 4; i++){
        uCurve[i] = getBezierCurve(controlPoints + (i * 4), u);
    }
    
    return getBezierCurve(uCurve, v);
}
