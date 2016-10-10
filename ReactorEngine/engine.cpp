#include "main.hpp"

Engine::Engine() {
    previousTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    
    Mesh *mesh = new Mesh("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/teapot.obj",
                          "/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/world_map.bmp");
    renderer = new Renderer(mesh);
    
    compileShaders();
}

/**
 * Source
 * 1. http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
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
    
    string vs = readFile("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/shader.vs");
    string fs = readFile("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/shader.fs");
    
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
    
    cout << 1.0 / Time::deltaTime << " FPS" << endl;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer->update(transformationMatLoc);
}
