#include "main.hpp"
#include "scene_main.hpp"
#include <unistd.h>

Engine *engine;

Texture *skyboxTextures[6];
GLuint textureObjId;
GLuint samplerId;

void update() {
    //======================================================================
    //======================================================================
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObjId);
    
    //======================================================================
    //======================================================================
    
    engine->update();
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    engine->onKeyPressed(key);
}

void mouse(int x, int y) {
    engine->onMouse(x, y);
}

int main(int argc, char* argv[]) {
    // glutInit() MUST be called from main() since it needs an UNEDITED argc and an UNEDITED argv.
    // https://www.opengl.org/resources/libraries/glut/spec3/node10.html
    glutInit(&argc, argv);
    
//    engine = new Engine(new SceneMain());
    engine = new Engine();
    engine->loadScene(new SceneMain);
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    glutSpecialFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    
//    glutGameModeString("1920x1200@60");
//    glutEnterGameMode();
    
    //==================================
    //==================================
    
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureObjId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObjId);
    
    skyboxTextures[0] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/posx.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_X, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, skyboxTextures[0]->width, skyboxTextures[0]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[0]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    skyboxTextures[1] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/negx.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_X, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, skyboxTextures[1]->width, skyboxTextures[1]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[1]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    skyboxTextures[2] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/posy.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Y, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, skyboxTextures[2]->width, skyboxTextures[2]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[2]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    skyboxTextures[3] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/negy.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, skyboxTextures[3]->width, skyboxTextures[3]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[3]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    skyboxTextures[4] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/posz.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Z, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, skyboxTextures[4]->width, skyboxTextures[4]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[4]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    skyboxTextures[5] = new Texture("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/negz.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, textureObjId);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, skyboxTextures[5]->width, skyboxTextures[5]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyboxTextures[5]->data);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenSamplers(1, &samplerId);
    glSamplerParameteri(samplerId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(samplerId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    //==========================================================================
    //==========================================================================
    
    glutMainLoop();
    
    return 0;
}
