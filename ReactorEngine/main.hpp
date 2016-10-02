#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <GLUT/glut.h>
#endif

#ifdef WIN32
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "vector3.hpp"
#include "matrix.hpp"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define WINDOW_TITLE "Reactor Engine"

#define INFO_LOG_BUF_LEN 1024

#endif
