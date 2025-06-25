#pragma once

#include "../Config/namespace.h"
#include "../Config/enumerations.h"

#include "Models/Object.h"

#include "Cameras/Orthographic.h"
#include "Cameras/Perspective.h"

#include "Physics/Vector.h"

#include "Physics/Particle.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/RenderParticle.h"
#include "Physics/ForceGenerator.h"
#include "Physics/ForceRegistry.h"
#include "Physics/GravityForceGenerator.h"
#include "Physics/DragForceGenerator.h"
#include "Physics/RenderParticleFactory.h"

/* 
    Game Class
        - Contains the sphere and the orthographic camera
        - Where the main game loop is located
*/
class Game {
private:
    // Window information
    GLFWwindow* window;
    float windowWidth;
    float windowHeight;

    // Sphere Object and VAO
    Model3D* sphereObj;
    GLuint sphereVAO;
    
    // Orthographic camera
    Orthographic* orthoCam;
    Perspective* persCam;

    CAM_TYPE camOn = ORTHOGRAPHIC;
    bool play = false;
    float inputCooldown = 0;

    list<RenderParticle*> renderParticles;
public:
    //CONSTRUCTORS
    Game();
    Game(GLFWwindow* window, float windowWidth, float windowHeight);

    //FUNCTIONS
    void start();
    void initialize();
    void run();
    void cleanRenderParticles();

    void checkInput();
    void setVAO(GLuint* VAO, int type);
   
    //DECONSTRUCTOR
    ~Game();
};