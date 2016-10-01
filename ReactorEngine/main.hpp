#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

using namespace std;

#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#endif

#ifdef WIN32
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "vector3.hpp"
#include "matrix.hpp"

#endif
