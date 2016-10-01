#include "main.hpp"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define WINDOW_TITLE "Reactor Engine"

GLuint vbo;

void update() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);
    
    glutDisplayFunc(update);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    Vector3 vertices[3];
    vertices[0] = Vector3(-1.0, -1.0, 0.0);
    vertices[1] = Vector3(1.0, -1.0, 0.0);
    vertices[2] = Vector3(0.0, 1.0, 0.0);
    
    glGenBuffers(1, &vbo); // vbo = new vbo(1);   1 is its size
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    int temp = sizeof(vertices);
    
    glutMainLoop();
    
    return 0;
}
