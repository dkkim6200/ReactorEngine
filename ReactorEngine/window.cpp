#include "main.hpp"

int Window::width;
int Window::height;

void Window::init() {
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
}
