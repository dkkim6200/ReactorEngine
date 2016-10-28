#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <sstream>
#include <vector>
#include <map>

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

#include "time.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "matrix.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "game_object.hpp"
#include "system.hpp"
#include "render_system.hpp"
#include "engine.hpp"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define WINDOW_TITLE "Reactor Engine"

#define INFO_LOG_BUF_LEN 1024

#define NUM_VERTICES_PER_PATCH 16

// class Component
#define COMPONENT_TRANSFORM 0
#define COMPONENT_RENDERER 1

extern Engine *engine;

#endif
