#include "main.hpp"

Engine *engine;

int gameObjectId1;
int gameObjectId2;
float rotation = 0;

void update() {
    engine->update();
    
    GameObject *gameObject = engine->getGameObject(gameObjectId1);
    gameObject->transform->rotation = Vector3(0, 0, rotation);
    
    rotation += 90.0f * M_PI / 180.0f * Time::deltaTime;
    
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
    engine->addGameObject(gameObject1);
    gameObject1->transform->setParent(NULL);
    gameObjectId1 = gameObject1->getId();
    
    gameObject1->transform->position = Vector3(1, 0, 5);
    gameObject1->transform->rotation = Vector3(0, 0, 0);
    gameObject1->transform->scale = Vector3(1, 1, 1) / 10;
    
    Renderer *renderer1 = (Renderer *)gameObject1->addComponent(COMPONENT_RENDERER);
    Mesh *teapotMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/teapot.obj",
                                "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/world_map.bmp");
    renderer1->mesh = teapotMesh;
    
    //=====================================================================
    
    GameObject *gameObject2 = new GameObject();
    engine->addGameObject(gameObject2);
    gameObject2->transform->setParent(engine->getGameObject(gameObject1->getId())->transform);
    gameObjectId2 = gameObject2->getId();
    
    gameObject2->transform->position = Vector3(-1, 0, 0);
    gameObject2->transform->rotation = Vector3(0, 0, 0);
    gameObject2->transform->scale = Vector3(1, 1, 1) / 10;
    
    Renderer *renderer2 = (Renderer *)gameObject2->addComponent(COMPONENT_RENDERER);
    Mesh *cubeMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/cube.obj",
                              "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/world_map.bmp");
    renderer2->mesh = cubeMesh;
    
    //======================================================================
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}
