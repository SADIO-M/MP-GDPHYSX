#pragma once

#include "../Config/namespace.h"
#include "../Config/enumerations.h"

#include "Models/Object.h"

#include "Cameras/Orthographic.h"

#include "Physics/Vector.h"

#include "Physics/Particle.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/RenderParticle.h"
#include "Physics/ForceGenerator.h"
#include "Physics/ForceRegistry.h"
#include "Physics/GravityForceGenerator.h"
#include "Physics/DragForceGenerator.h"

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
    vector<Model3D*> allModels;
    GLuint sphereVAO;
    
    // Orthographic camera
    Orthographic* orthoCam;

public:
    //CONSTRUCTORS
    Game();
    Game(GLFWwindow* window, float windowWidth, float windowHeight);

    //FUNCTIONS
    void start();
    void initialize();
    void run();

    void setVAO(GLuint* VAO, int type);
   
    //DECONSTRUCTOR
    ~Game();
};