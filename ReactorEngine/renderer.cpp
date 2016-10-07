#include "main.hpp"

Renderer::Renderer(Mesh *mesh){
    this->mesh = mesh;
    
    rotation = 0.0f;
    rotationAxis = Vector3(1.0f, 1.0f, 0.0f);
    scale = Vector3(0.3f, 0.3f, 0.3f);
    translation = Vector3(0.0f, 0.0f, 10.0f);
    
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &uvboId);
    
    texture = new Texture("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/world_map.bmp");
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
    
    //================================================================
    // Render each patches
    //================================================================
    
    texture->bind(GL_TEXTURE0);
    
    glEnableVertexAttribArray(0); // 'position' variable
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vector3), mesh->vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(1); // 'textureCoord' variable
    glBindBuffer(GL_ARRAY_BUFFER, uvboId);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, mesh->numUVs * sizeof(Vector2), mesh->uvs, GL_STATIC_DRAW);
    
//    glDrawElements(GL_TRIANGLES, mesh->numVertexIndices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
