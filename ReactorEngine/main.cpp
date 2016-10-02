#include "main.hpp"

GLuint vbo;
GLuint vao;
Vector3 vertices[3];

void update() {
    glClear(GL_COLOR_BUFFER_BIT);

    vertices[0].x += 0.01;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

/**
 * Source
 * 1. http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 */
string readFile(string fileName) {
    ifstream file(fileName);
    stringstream buffer;
    
    buffer << file.rdbuf();
    
    return buffer.str();
}

void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType) {
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

void compileShaders() {
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
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    vertices[0] = Vector3(-1.0, -1.0, 0.0);
    vertices[1] = Vector3(1.0, -1.0, 0.0);
    vertices[2] = Vector3(0.0, 1.0, 0.0);
    
    // http://swchoi06.tistory.com/entry/OpenGL-validation-failed-no-vertex-array-object-bound
    // https://www.opengl.org/discussion_boards/showthread.php/175839-OSX-GL3-2-and-VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo); // vbo = new vbo(1);   1 is its size
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    compileShaders();
    
    glutMainLoop();
    
    return 0;
}
