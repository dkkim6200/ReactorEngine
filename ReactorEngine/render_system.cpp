#include "main.hpp"

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::update(GameObject *gameObject) {
    Transform *transform = (Transform *)gameObject->getComponent(COMPONENT_TRANSFORM);
    Renderer *renderer = (Renderer *)gameObject->getComponent(COMPONENT_RENDERER);
    
    if (renderer != NULL &&
        renderer->mesh != NULL) {
        //================================================================
        // Update Matrices
        //================================================================
        
        Matrix projectionMat = Matrix::getProjectionMat((float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f, 30.0f * M_PI / 180.0f);
        
        Matrix transformationMat = projectionMat * transform->getWorldTransformationMat();
        glUniformMatrix4fv(engine->transformationMatLoc, 1, true, transformationMat.m);
        
        //================================================================
        // Render each patches
        //================================================================
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer->mesh->texture->textureObjId);
        
        glEnableVertexAttribArray(0); // 'position' variable
        glEnableVertexAttribArray(1); // 'textureCoord' variable
        
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vboId);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glBufferData(GL_ARRAY_BUFFER, renderer->mesh->vertices.size() * sizeof(Vector3), &renderer->mesh->vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, renderer->uvboId);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
        glBufferData(GL_ARRAY_BUFFER, renderer->mesh->uvs.size() * sizeof(Vector2), &renderer->mesh->uvs[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer->mesh->indices.size() * sizeof(unsigned int), &renderer->mesh->indices[0], GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES, renderer->mesh->indices.size(), GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}
