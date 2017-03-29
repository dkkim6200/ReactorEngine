#include "main.hpp"

Engine *engine;

int gameObjectId1;
int gameObjectId2;

#define FACTOR 0.1

int direction = 1;
double scale = 0;

void update() {
    engine->update();
    
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    
    double rotation = RAD(90.0) * Time::deltaTime;
    scale += Time::deltaTime;
    double scaleFactor = abs(sin(scale) * FACTOR);
    
    Vector3 gameObject1Pos = gameObject1->transform->getWorldPosition();
    
    // Test Transform::translate(). See if the GameObject moves back and forth along its side.
    if (gameObject1Pos.x > 1) {
        direction = -1;
    } else if (gameObject1Pos.x < -1) {
        direction = 1;
    }
    gameObject1->transform->translate(Vector3(direction * 1 * Time::deltaTime, 0, 0));
    
    // Test Transform::rotate(). See if the GameObject rotates without any gimbal lock.
    gameObject1->transform->rotate(Vector3(rotation, rotation, rotation));
    
    // Test Transform::scale. See if it actually changes its size
    gameObject1->transform->scale = Vector3(scaleFactor, scaleFactor, scaleFactor);
    
    // Test Transform::getWorldRotation. See if the rotation being printed is correct.
    cout << DEG(gameObject1->transform->getWorldRotation().toEulerAngles()) << endl;
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    
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
    // User Programmable Editable Region Start
    //=====================================================================
    
    //=====================================================================
    
    GameObject *gameObject1 = new GameObject();
    engine->addGameObject(gameObject1);
    gameObject1->transform->setParent(NULL);
    gameObjectId1 = gameObject1->getId();
    
    gameObject1->transform->position = Vector3(0, 0, 3);
    gameObject1->transform->rotation = Quaternion(RAD(-30), RAD(-45), RAD(-45));
    gameObject1->transform->scale = Vector3(0.1, 0.1, 0.1);
    
    Renderer *renderer1 = (Renderer *)gameObject1->addComponent(COMPONENT_RENDERER);
    Mesh *teapotMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/cop_mesh.obj",
                                "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehicle_Police.bmp");
    renderer1->mesh = teapotMesh;
    
    //=====================================================================
    
    GameObject *gameObject2 = new GameObject();
    engine->addGameObject(gameObject2);
    gameObject2->transform->setParent(gameObject1->transform);
    gameObjectId2 = gameObject2->getId();
    
    gameObject2->transform->position = Vector3(3, 0, 0);
    gameObject2->transform->rotation = Quaternion(0, 0, 0);
    gameObject2->transform->scale = Vector3(0.5, 0.5, 0.5);
    
    Renderer *renderer2 = (Renderer *)gameObject2->addComponent(COMPONENT_RENDERER);
    Mesh *cubeMesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/ambo_mesh.obj",
                              "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehice_Ambulance.bmp");
    renderer2->mesh = cubeMesh;
    
    //======================================================================
    
    //=====================================================================
    // User Programmable Editable Region End
    //=====================================================================
    
    glutDisplayFunc(update);
    glutIdleFunc(idle);
    glutSpecialFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
