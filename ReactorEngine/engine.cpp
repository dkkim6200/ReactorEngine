#include "main.hpp"

Engine::Engine() {
    previousTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    
    ifstream teapotFile;
    teapotFile.open("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/teapot");
    
    string s;
    getline(teapotFile, s);
    numTeapotPatches = atoi(s.c_str());
    teapotPatches = new int*[numTeapotPatches];
    
    for (int i = 0; i < numTeapotPatches; i++) {
        teapotPatches[i] = new int[NUM_VERTICES_PER_PATCH];
        
        getline(teapotFile, s);
        stringstream ss(s);
        
        string token;
        for (int j = 0; getline(ss, token, ','); j++) {
            // Putting getline in the incremental side will do no good, since it will only get executed when the code block below is done executing, which means that the initial value of 'token' would be uninitialized, so atoi() will return 0 or other jiberish.
            teapotPatches[i][j] = atoi(token.c_str());
        }
    }
    
    getline(teapotFile, s);
    numTeapotVertices = atoi(s.c_str());
    teapotVertices = new Vector3[numTeapotVertices];
    
    for (int i = 0; i < numTeapotVertices; i++) {
        getline(teapotFile, s);
        stringstream ss(s);
        
        string token;
        
        getline(ss, token, ',');
        teapotVertices[i].x = atof(token.c_str());
        getline(ss, token, ',');
        teapotVertices[i].y = atof(token.c_str());
        getline(ss, token, ',');
        teapotVertices[i].z = atof(token.c_str());
    }
    
    Mesh *mesh = new Mesh(teapotVertices, numTeapotVertices, teapotPatches, numTeapotPatches);
    
    for (int i = 0; i < numTeapotVertices; i++) {
        cout << teapotVertices[i] << endl;
    }
    
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
    
    projectionMatLoc = glGetUniformLocation(shaderProgram, "projectionMat");
    if (projectionMatLoc == 0xFFFFFFFF) {
        cout << "Error getting 'projectionMatLoc' variable from shaderProgram." << endl;
        exit(1);
    }
    
    scaleMatLoc = glGetUniformLocation(shaderProgram, "scaleMat");
    if (scaleMatLoc == 0xFFFFFFFF) {
        cout << "Error getting 'scaleMatLoc' variable from shaderProgram." << endl;
        exit(1);
    }
    
    rotationMatLoc = glGetUniformLocation(shaderProgram, "rotationMat");
    if (rotationMatLoc == 0xFFFFFFFF) {
        cout << "Error getting 'rotationMat' variable from shaderProgram." << endl;
        exit(1);
    }
    
    translationMatLoc = glGetUniformLocation(shaderProgram, "translationMat");
    if (translationMatLoc == 0xFFFFFFFF) {
        cout << "Error getting 'translationMatLoc' variable from shaderProgram." << endl;
        exit(1);
    }
    
    colorVecLoc = glGetUniformLocation(shaderProgram, "colorVec");
    if (colorVecLoc == 0xFFFFFFFF) {
        cout << "Error getting 'colorVec' variable from shaderProgram." << endl;
        exit(1);
    }
}

void Engine::update() {
    previousTime = currentTime;
    currentTime = std::chrono::high_resolution_clock::now();
    
    Time::deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
    
    cout << 1.0 / Time::deltaTime << " FPS" << endl;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer->update(projectionMatLoc, scaleMatLoc, rotationMatLoc, translationMatLoc, colorVecLoc);
}
