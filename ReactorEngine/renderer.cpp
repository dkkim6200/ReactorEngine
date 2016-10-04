#include "main.hpp"

Renderer::Renderer(Mesh *mesh){
    this->mesh = mesh;
    
    rotation = 45.0f;
    rotationAxis = Vector3(1.0f, 1.0f, 0.0f);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    translation = Vector3(0.0f, 0.0f, 0.0f);
    
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vector3), mesh->vertices, GL_STATIC_DRAW);
}

Renderer::~Renderer() {
    delete mesh;
}

void Renderer::update(GLuint scaleMatLoc, GLuint rotationMatLoc, GLuint translationMatLoc) { // Render mesh
    
//    rotation += 90.0f * Time::deltaTime;
//    rotation = fmod(rotation, 1080.0f);
    
    Matrix scaleMat = Matrix::getScaleMat(scale);
    glUniformMatrix4fv(scaleMatLoc, 1, true, scaleMat.m);
    
    Matrix rotationMat = Matrix::getRotationMat(rotationAxis, rotation * M_PI / 180.0f);
    glUniformMatrix4fv(rotationMatLoc, 1, true, rotationMat.m);
    
    Matrix translationMat = Matrix::getTranslationMat(translation);
    glUniformMatrix4fv(translationMatLoc, 1, true, translationMat.m);
    
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vector3), mesh->vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);
    
    glDisableVertexAttribArray(0);
}

