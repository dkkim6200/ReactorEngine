#include "main.hpp"

Engine *engine;

void update() {
    engine->update();
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    
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
    
    engine = new Engine();
    
    //=====================================================================
    
    GameObject *gameObject1 = new GameObject();
    
    Transform *transform1 = (Transform *)gameObject1->getComponent(COMPONENT_TRANSFORM);
    transform1->position = Vector3(0, 0, 5);
    transform1->rotation = Vector3(0, 0, 0);
    transform1->scale = Vector3(1, 1, 1) / 10;
    
    Renderer *renderer1 = (Renderer *)gameObject1->addComponent(COMPONENT_RENDERER);
    Mesh *teapotMesh = new Mesh("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/teapot.obj",
                                "/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/world_map.bmp");
    renderer1->mesh = teapotMesh;
    
    //=====================================================================
    
    GameObject *gameObject2 = new GameObject();
    Transform *transform2 = (Transform *)gameObject2->getComponent(COMPONENT_TRANSFORM);
    transform2->position = Vector3(0, 0, 2);
    transform2->rotation = Vector3(0, 0, 0);
    transform2->scale = Vector3(1, 1, 1) / 10;
    
    Renderer *renderer2 = (Renderer *)gameObject2->addComponent(COMPONENT_RENDERER);
    Mesh *cubeMesh = new Mesh("/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/cube.obj",
                              "/Users/DaekunKim/Documents/Programming Related/ReactorEngine/ReactorEngine/world_map.bmp");
    renderer2->mesh = cubeMesh;
    
    //======================================================================
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}
