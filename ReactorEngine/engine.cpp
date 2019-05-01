#include "main.hpp"
#include <unistd.h>

Engine::Engine() {
    initOpenGL();
    
    // Reactor Engine initialization
    
    curScene = NULL;
    
    Input::init();
    
    gameObjects = new unordered_map<int, GameObject *>();
    
    componentContainers = new unordered_map<TypeInfo, vector<Component *> *>();
    scriptContainers = new unordered_map<TypeInfo, vector<Script *> *>();
    scripts = new vector<Script *>();
    
    systems = new vector<System *>();
    systems->push_back(new RenderSystem());
    systems->push_back(new TimeSystem());
    systems->push_back(new ScriptSystem());
}

void Engine::initOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();
    
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version supported: " << glGetString(GL_VERSION) << endl;
    
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
}

void Engine::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < systems->size(); i++) {
        systems->at(i)->update();
    }
    
    if (1.0 / Time::deltaTime > MAX_FPS) {
        usleep(500000.0 * (1.0 / MAX_FPS - Time::deltaTime));
    }
}

void Engine::loadScene(Scene *scene) {
    curScene = scene;
}

GameObject *Engine::getGameObject(int id) {
    if (gameObjects->find(id) != gameObjects->end()) {
        return gameObjects->at(id);
    }
    else {
        return NULL;
    }
}

void Engine::addGameObject(GameObject *gameObject) {
    (*gameObjects)[gameObject->getId()] = gameObject;
}

void Engine::removeComponent(Component *component) {
    if (dynamic_cast<Script *>(component)) {
        vector<Script *> *curContainer = (*scriptContainers)[component->type];
        
        curContainer->erase(std::remove(curContainer->begin(), curContainer->end(), (Script *)component));
    }
    else {
        vector<Component *> *curContainer = (*componentContainers)[component->type];
        
        curContainer->erase(std::remove(curContainer->begin(), curContainer->end(), component));
    }
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
    
    Input::mouseX = (x / INIT_SCREEN_WIDTH) - 0.5;
    Input::mouseY = -((y / INIT_SCREEN_HEIGHT) - 0.5);
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
