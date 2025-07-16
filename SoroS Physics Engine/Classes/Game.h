#pragma once

//// CONFIGURATIONS
#include "../Config/namespace.h"
#include "../Config/enumerations.h"
/// MODELS
#include "Models/Object.h"
/// CAMERAS
#include "Cameras/Orthographic.h"
#include "Cameras/Perspective.h"
/// PHYSICS-RELATED
#include "Physics/Vector.h"
#include "Physics/Particle.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/RenderParticle.h"
#include "Physics/ForceGenerator.h"
#include "Physics/ForceRegistry.h"
#include "Physics/GravityForceGenerator.h"
#include "Physics/DragForceGenerator.h"
#include "Physics/RenderParticleFactory.h"
#include "Physics/ParticleContact.h"
#include "Physics/ContactResolver.h"
#include "Physics/Springs/AnchoredSpring.h"
#include "Physics/Springs/ParticleSpring.h"
#include "Physics/Links/Rod.h"
#include "Physics/Links/Cable.h"

/* 
    Game Class
        - Contains the sphere and cameras
        - Where the main game loop is located
        - Fixed Update handles all physics-related things (like physics world and render particles)
        - Handles player inputs

    [Created by: Megan Sadio and Yza Montuerto]
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

    //Checks current camera 
    CAM_TYPE camOn = ORTHOGRAPHIC;
    //For play or pausing
    bool play = false;
    //Input cooldown
    float inputCooldown = 0;

public:
    //CONSTRUCTORS
    Game();
    Game(GLFWwindow* window, float windowWidth, float windowHeight);

    //FUNCTIONS
    void start();
    void initialize();
    void run();

    void cleanRenderParticles(list<RenderParticle*>* renderParticles);
    void checkInput();
    void setVAO(GLuint* VAO, int type);
   
    //DECONSTRUCTOR
    ~Game();
};