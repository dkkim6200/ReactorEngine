#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <typeindex>
#include <list>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

class Engine;
extern Engine *engine;

#include "type_info.hpp"
#include "util.hpp"
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

#include "system.hpp"
#include "script.hpp"
#include "render_system.hpp"
#include "time_system.hpp"
#include "input_system.hpp"

#include "event.hpp"
#include "key_down_event.hpp"
#include "key_up_event.hpp"
#include "script_system.hpp"

#include "scene.hpp"
#include "engine.hpp"
#include "game_object.hpp"

#define INIT_SCREEN_WIDTH 800
#define INIT_SCREEN_HEIGHT 600

#define WINDOW_TITLE "Reactor Engine"

#define VERTEX_SHADER_FILE "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/shader.vs"
#define FRAGEMENT_SHADER_FILE "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/shader.fs"

#define INFO_LOG_BUF_LEN 1024

#define NUM_VERTICES_PER_PATCH 16

#define MAX_FPS 60
#define SHOW_FPS false

#define RAD(x) x*3.14159265359/180.0
#define DEG(x) x*180.0/3.14159265359

#endif
