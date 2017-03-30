#include "main.hpp"

Engine *engine;

int gameObjectId1;
int gameObjectId2;

#define FACTOR 0.1

void update() {
    engine->update();
    
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    
    double rotation = RAD(90.0) * Time::deltaTime;
    
    cout << "====================\n\n" << endl;
    cout << "Position: " << gameObject1->transform->getWorldPosition() << endl;
    cout << "Rotation: " << DEG(gameObject1->transform->getWorldRotation().toEulerAngles()) << endl;
    cout << "Scale: " << gameObject1->transform->getWorldScale() << endl;
    
    // Test Transform::rotate(). See if the GameObject rotates without any gimbal lock.
    gameObject1->transform->rotate(Vector3(0, rotation, 0));
    
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    GameObject *gameObject1 = engine->getGameObject(gameObjectId1);
    
    switch (key) {
        case GLUT_KEY_UP:
            gameObject1->transform->position += Vector3(0, 1, 0) * FACTOR;
            break;
            
        case GLUT_KEY_DOWN:
            gameObject1->transform->position += Vector3(0, -1, 0) * FACTOR;
            break;
            
        case GLUT_KEY_LEFT:
            gameObject1->transform->position += Vector3(-1, 0, 0) * FACTOR;
            break;
            
        case GLUT_KEY_RIGHT:
            gameObject1->transform->position += Vector3(1, 0, 0) * FACTOR;
            break;
            
        case 'w':
            gameObject1->transform->position += Vector3(0, 0, 1) * FACTOR;
            break;
            
        case 's':
            gameObject1->transform->position += Vector3(0, 0, -1) * FACTOR;
            break;
            
        case 'q':
            exit(0);
            break;
            
        default:
            break;
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
    
    gameObject1->transform->position = Vector3(0, -0.5, 4);
    gameObject1->transform->rotation = Quaternion::identity();
    gameObject1->transform->scale = Vector3(0.1, 0.1, 0.1);
    
    Renderer *renderer1 = (Renderer *)gameObject1->addComponent(COMPONENT_RENDERER);
//    renderer1->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/cop_mesh.obj",
//                                "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Vehicle_Police.bmp");
    renderer1->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/road_t_mesh.obj",
                               "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Road.bmp");
    
    //=====================================================================
    
    GameObject *gameObject2 = new GameObject();
    engine->addGameObject(gameObject2);
    gameObject2->transform->setParent(gameObject1->transform);
    gameObjectId2 = gameObject2->getId();
    
    gameObject2->transform->position = Vector3(0, 0, 10);
    gameObject2->transform->rotation = Quaternion::identity();
    gameObject2->transform->scale = Vector3(1, 1, 1);
    
    Renderer *renderer2 = (Renderer *)gameObject2->addComponent(COMPONENT_RENDERER);
    renderer2->mesh = new Mesh("/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/models/store_corner_mesh.obj",
                              "/Users/DaekunKim/Documents/Programming/ReactorEngine/ReactorEngine/models/simple_town/textures/Building03c.bmp");
    
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
