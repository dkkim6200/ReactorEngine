#include "main.hpp"

Renderer::Renderer(Mesh *mesh){
    this->mesh = mesh;
    
    rotation = 0.0f;
    rotationAxis = Vector3(1.0f, 1.0f, 0.0f);
    scale = Vector3(0.3f, 0.3f, 0.3f);
    translation = Vector3(0.0f, 0.0f, 10.0f);
    
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &uvboId);
    glGenBuffers(1, &iboId);
}

Renderer::~Renderer() {
    delete mesh;
}

void Renderer::update(GLuint transformationMatLoc) { // Render mesh
    
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
    Matrix scaleMat = Matrix::getScaleMat(scale);
    Matrix rotationMat = Matrix::getRotationMat(rotationAxis, rotation * M_PI / 180.0f);
    Matrix translationMat = Matrix::getTranslationMat(translation);
    
    Matrix transformationMat = projectionMat * translationMat * rotationMat * scaleMat;
    glUniformMatrix4fv(transformationMatLoc, 1, true, transformationMat.m);
    
    //================================================================
    // Render each patches
    //================================================================
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->texture->textureObjId);
    
    glEnableVertexAttribArray(0); // 'position' variable
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vector3), &mesh->vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(1); // 'textureCoord' variable
    glBindBuffer(GL_ARRAY_BUFFER, uvboId);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, mesh->uvs.size() * sizeof(Vector2), &mesh->uvs[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0], GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
