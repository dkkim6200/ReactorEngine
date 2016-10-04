#include "main.hpp"

Engine *engine;

void update() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    engine->update();
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // http://swchoi06.tistory.com/entry/OpenGL-validation-failed-no-vertex-array-object-bound
    // https://www.opengl.org/discussion_boards/showthread.php/175839-OSX-GL3-2-and-VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    engine = new Engine();
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}
