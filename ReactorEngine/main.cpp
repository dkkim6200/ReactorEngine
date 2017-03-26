#include "main.hpp"

Engine *engine;

int gameObjectId1;
int gameObjectId2;
float rotation = 0;

#define FACTOR 0.1

void update() {
    engine->update();
    /*
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    gameObject1->transform->rotation = Vector3(0, 0, rotation);
    
    rotation += 90.0f * M_PI / 180.0f * Time::deltaTime;
    */
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    GameObject *gameObject2 = engine->getGameObject(gameObjectId2);
    
    if (key == GLUT_KEY_UP) {
        gameObject1->transform->position += Vector3(0, 1, 0) * FACTOR;
    } else if (key == GLUT_KEY_DOWN) {
        gameObject1->transform->position += Vector3(0, -1, 0) * FACTOR;
    } else if (key == GLUT_KEY_LEFT) {
        gameObject1->transform->position += Vector3(-1, 0, 0) * FACTOR;
    } else if (key == GLUT_KEY_RIGHT) {
        gameObject1->transform->position += Vector3(1, 0, 0) * FACTOR;
    } else if (key == 'w') {
        gameObject1->transform->position += Vector3(0, 0, 1) * FACTOR;
    } else if (key == 's') {
        gameObject1->transform->position += Vector3(0, 0, -1) * FACTOR;
    } else if (key == 'q') {
        exit(0);
    }
    
    engine->keyboardDetected(key);
}

int main(int argc, char* argv[]) {
    // glutInit() MUST be called from main() since it needs an UNEDITED argc and an UNEDITED argv.
    // https://www.opengl.org/resources/libraries/glut/spec3/node10.html
    glutInit(&argc, argv);
    
    engine = new Engine();
    
    //=====================================================================
    
    GameObject *gameObject1 = new GameObject();
    engine->addGameObject(gameObject1);
    gameObject1->transform->setParent(NULL);
    gameObjectId1 = gameObject1->getId();
    
    gameObject1->transform->position = Vector3(0, 0, 0);
    gameObject1->transform->rotation = Vector3(0, 0, 0);
    gameObject1->transform->scale = Vector3(1, 1, 1) * FACTOR;
    
    Renderer *renderer1 = (Renderer *)gameObject1->addComponent(COMPONENT_RENDERER);
    Mesh *teapotMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/cop_mesh.obj",
                                "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehicle_Police.bmp");
    renderer1->mesh = teapotMesh;
    
    //=====================================================================
    
    GameObject *gameObject2 = new GameObject();
    engine->addGameObject(gameObject2);
    gameObject2->transform->setParent(gameObject1->transform);
    gameObjectId2 = gameObject2->getId();
    
    gameObject2->transform->position = Vector3(1, 0, 0);
    gameObject2->transform->rotation = Vector3(0, 0, 0);
    gameObject2->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer2 = (Renderer *)gameObject2->addComponent(COMPONENT_RENDERER);
    Mesh *cubeMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/ambo_mesh.obj",
                              "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehice_Ambulance.bmp");
    renderer2->mesh = cubeMesh;
    
    //======================================================================
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    glutSpecialFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
