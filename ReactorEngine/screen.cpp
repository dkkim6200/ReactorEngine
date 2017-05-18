#include "main.hpp"

int Screen::width;
int Screen::height;

void Screen::init() {
    width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT);
}
