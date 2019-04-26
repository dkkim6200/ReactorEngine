#include "main.hpp"
#include "scene_main.hpp"
#include <unistd.h>

Engine *engine;

Texture *skyboxTextures[6];
GLuint textureObjId;
GLuint samplerId;

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        engine->onKeyPressed(key);
    }
    else if (action == GLFW_RELEASE) {
        engine->onKeyRelease(key);
    }
}

void mouse(GLFWwindow *window, double x, double y) {
    engine->onMouse(x, y);
}

int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version supported " << glGetString(GL_VERSION) << endl;
    
//    engine = new Engine(new SceneMain());
    engine = new Engine();
    engine->loadScene(new SceneMain);
    
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouse);
    
    while(!glfwWindowShouldClose(window)) {
        //======================================================================
        //======================================================================
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureObjId);
        
        //======================================================================
        //======================================================================
        
        engine->update();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
