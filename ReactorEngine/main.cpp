#include "main.hpp"
#include "scene_main.hpp"
#include <unistd.h>

Engine *engine;

void update() {
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
    
    glutMainLoop();
    
    return 0;
}
