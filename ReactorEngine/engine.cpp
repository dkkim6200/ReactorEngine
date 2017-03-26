#include "main.hpp"

Engine::Engine() {
    // OpenGL Initialization
    
    // https://www.opengl.org/discussion_boards/showthread.php/172472-GL_DEPTH_TEST-not-working
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_TEXTURE_2D);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // http://swchoi06.tistory.com/entry/OpenGL-validation-failed-no-vertex-array-object-bound
    // https://www.opengl.org/discussion_boards/showthread.php/175839-OSX-GL3-2-and-VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Reactor Engine initialization
    
    previousTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    
    systems = new vector<System *>();
    systems->push_back(new RenderSystem());
    
    gameObjects = new map<int, GameObject *>();
    
    compileShaders();
}

/**
 Source
 1. http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 */
string Engine::readFile(string fileName) {
    ifstream file(fileName);
    stringstream buffer;
    
    buffer << file.rdbuf();
    
    return buffer.str();
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
    GLuint shaderProgram = glCreateProgram();
    
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
    
    GLuint sampler = glGetUniformLocation(shaderProgram, "sampler");
    if (sampler == 0xFFFFFFFF) {
        cout << "Error getting 'sampler' variable from shaderProgram." << endl;
        exit(1);
    }
    glUniform1i(sampler, 0);
}

void Engine::update() {
    previousTime = currentTime;
    currentTime = std::chrono::high_resolution_clock::now();
    
    Time::deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
    
    if (SHOW_FPS) {
        cout << 1.0 / Time::deltaTime << " FPS" << endl;
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < systems->size(); i++) {
        for (auto it = gameObjects->begin(); it != gameObjects->end(); it++) {
            systems->at(i)->update(it->second);
        }
    }
}

void Engine::keyboardDetected(int key) {
    
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
    gameObjects->emplace(gameObject->getId(), gameObject);
}
