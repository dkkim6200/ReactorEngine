#include "main.hpp"

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::start() {
    initOpenGL();
    
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
}

void RenderSystem::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto it = engine->gameObjects->begin(); it != engine->gameObjects->end(); it++) {
        if (!it->second->hasComponent<Renderer>()) {
            continue;
        }
        
        GameObject *gameObject = it->second;
        
        Transform *transform = gameObject->transform;
        Renderer *renderer = gameObject->getComponent<Renderer>();
        
        //================================================================
        // Update Matrices
        //================================================================
        
        GameObject *cameraGameObject = Camera::mainCamera->gameObject;
        
        Matrix projectionMat = Matrix::getProjectionMat(INIT_SCREEN_WIDTH / INIT_SCREEN_HEIGHT,
                                                        Camera::mainCamera->nearClipPlane,
                                                        Camera::mainCamera->farClipPlane,
                                                        Camera::mainCamera->fov);
        
        Matrix cameraTranslationMat = Matrix::getTranslationMat(cameraGameObject->transform->getWorldPosition() * -1);
        Matrix cameraRotationMat = Matrix::getRotationMat(cameraGameObject->transform->getWorldRotation());
        
        Matrix transformationMat = projectionMat * cameraRotationMat * cameraTranslationMat * transform->getWorldTransformationMat();
        glUniformMatrix4fv(transformationMatLoc, 1, true, transformationMat.m);
        
        //================================================================
        // Render each patches
        //================================================================
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer->mesh->texture->textureObjId);
        
        glEnableVertexAttribArray(0); // 'position' variable
        glEnableVertexAttribArray(1); // 'textureCoord' variable
        
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vboId);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glBufferData(GL_ARRAY_BUFFER, renderer->mesh->vertices.size() * sizeof(Vector3), &renderer->mesh->vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, renderer->uvboId);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
        glBufferData(GL_ARRAY_BUFFER, renderer->mesh->uvs.size() * sizeof(Vector2), &renderer->mesh->uvs[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->iboId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer->mesh->indices.size() * sizeof(unsigned int), &renderer->mesh->indices[0], GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES, renderer->mesh->indices.size(), GL_UNSIGNED_INT, 0);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}

void RenderSystem::initOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();
    
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    
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

void RenderSystem::addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType) {
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

void RenderSystem::compileShaders() {
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
    
    //    glUniform1i(sampler, 0);
}

