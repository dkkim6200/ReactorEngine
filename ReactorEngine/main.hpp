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
#include <algorithm>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <QApplication>

//#include <glm/glm.hpp>

#include "util.hpp"
#include "screen.hpp"
#include "window.hpp"
#include "time.hpp"
#include "input.hpp"
#include "vector3.hpp"
#include "vector2.hpp"
#include "quaternion.hpp"
#include "matrix.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "game_object.hpp"
#include "system.hpp"
#include "render_system.hpp"
#include "scene.hpp"
#include "engine.hpp"

#define INIT_SCREEN_WIDTH 800
#define INIT_SCREEN_HEIGHT 600

#define WINDOW_TITLE "Reactor Engine"

#define VERTEX_SHADER_FILE "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/shader.vs"
#define FRAGEMENT_SHADER_FILE "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/shader.fs"

#define INFO_LOG_BUF_LEN 1024

#define NUM_VERTICES_PER_PATCH 16

// class Component
#define COMPONENT_TRANSFORM 0
#define COMPONENT_RENDERER 1
#define COMPONENT_CAMERA 2

#define SHOW_FPS true

#define RAD(x) x*3.14159265359/180.0
#define DEG(x) x*180.0/3.14159265359

extern Engine *engine;

#endif
