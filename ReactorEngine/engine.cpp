#include "main.hpp"

Engine::Engine() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_TEXTURE_2D);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // http://swchoi06.tistory.com/entry/OpenGL-validation-failed-no-vertex-array-object-bound
    // https://www.opengl.org/discussion_boards/showthread.php/175839-OSX-GL3-2-and-VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    compileShaders();
    
    // Reactor Engine initialization
    
    curScene = NULL;
    
    Time::init();
    Input::init();
    Screen::init();
    Window::init();
}

void Engine::update() {
    Time::updateDeltaTime();
    
//    Screen::width = glutGet(GLUT_SCREEN_WIDTH);
//    Screen::height = glutGet(GLUT_SCREEN_HEIGHT);
//
//    Window::width = glutGet(GLUT_WINDOW_WIDTH);
//    Window::height = glutGet(GLUT_WINDOW_HEIGHT);
    
    if (SHOW_FPS) {
        cout << 1.0 / Time::deltaTime << " FPS" << endl;
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    curScene->update();
}

void Engine::loadScene(Scene *scene) {
    curScene = scene;
}

void Engine::onKeyPressed(int key) {
    Input::pressedKey = key;
}

void Engine::onKeyRelease(int key) {
    Input::pressedKey = NULL;
}

void Engine::onMouse(double x, double y) {
//    Input::mouseX = (x - (Window::width / 2)) / (Window::width / 2);
//    Input::mouseY = (y - (Window::height / 2)) / (Window::height / 2);
    
    Input::mouseX = (x / Window::width) - 0.5;
    Input::mouseY = -((y / Window::height) - 0.5);
}

void Engine::addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType) {
    GLuint shaderObj = glCreateShader(shaderType);
    
    // TODO: Check if shaderObj is properly read.
    
    const GLchar *codes[1]; // 1 shader code to be attached to shaderObj
    codes[0] = shaderText;
    
    GLint codeLengths[1];
    codeLengths[0] = strlen(shaderText);
    
    glShaderSource(shaderObj, 1, codes, codeLengths);
    glCompileShader(shaderObj);
    
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        GLchar infoLog[INFO_LOG_BUF_LEN];
        glGetShaderInfoLog(shaderObj, sizeof(infoLog), NULL, infoLog);
        cout << "Error compiling shader type " << shaderType << " : " << infoLog << endl;
        
        exit(1);
    }
    
    glAttachShader(shaderProgram, shaderObj);
}

void Engine::compileShaders() {
    shaderProgram = glCreateProgram();
    
    string vs = readFile(VERTEX_SHADER_FILE);
    string fs = readFile(FRAGEMENT_SHADER_FILE);
    
    // TODO: Check if vs and fs are properly read.
    
    addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
    
    GLint success = false;
    GLchar infoLog[INFO_LOG_BUF_LEN];
    
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        cout << "Error linking shader program: " << infoLog << endl;
        
        exit(1);
    }
    
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        cout << "Invalid shader program: " << infoLog << endl;
        
        exit(1);
    }
    
    glUseProgram(shaderProgram);
    
    transformationMatLoc = glGetUniformLocation(shaderProgram, "transformationMat");
    if (transformationMatLoc == 0xFFFFFFFF) {
        cout << "Error getting 'transformationMat' variable from shaderProgram." << endl;
        exit(1);
    }
    
    samplerLoc = glGetUniformLocation(shaderProgram, "sampler");
    if (samplerLoc == 0xFFFFFFFF) {
        cout << "Error getting 'sampler' variable from shaderProgram." << endl;
        exit(1);
    }
//    glUniform1i(sampler, 0);
}
