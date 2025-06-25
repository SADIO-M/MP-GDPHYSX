/*
////////// PHASE 1 : GDPHYSX - S22 //////////
    Submitted by:
        MONTUERTO, Yzabelle Anne A.
        SADIO, Megan Florence Sophia C.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

////////// EXTERNAL LIBRARIES //////////
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef TINYOBJ_H
    #define TINYOBJ_H
    #define TINYOBJLOADER_IMPLEMENTATION
    #include "tiny_obj_loader.h"
#endif

#ifndef STB_H
    #define STB_H
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <list>

////////// CLASSES //////////
/* GAME CLASS */
#include "Classes/Game.h"
/* SHADER CLASS */
#include "Classes/Shaders/Shader.h"
/* PHYSICS-RELATED CLASSES */
#include "Classes/Physics/Vector.h"
#include "Classes/Physics/Particle.h"
#include "Classes/Physics/PhysicsWorld.h"
#include "Classes/Physics/RenderParticle.h"
#include "Classes/Physics/ForceGenerator.h"
#include "Classes/Physics/ForceRegistry.h"
#include "Classes/Physics/GravityForceGenerator.h"
#include "Classes/Physics/DragForceGenerator.h"
#include "Classes/Physics/RenderParticleFactory.h"
/* MODEL-RELATED CLASSES */
#include "Classes/Models/Model3D.h"
#include "Classes/Models/Object.h"
/* CAMERA-RELATED CLASSES */
#include "Classes/Cameras/Camera.h"
#include "Classes/Cameras/Perspective.h"
#include "Classes/Cameras/Orthographic.h"

////////// CONFIGURATIONS //////////
#include "Config/namespace.h"
#include "Config/enumerations.h"

int main(void)
{
    GLFWwindow* window;
    //Window width and height
    float windowWidth  = 800.0f,
          windowHeight = 800.0f;

    if (!glfwInit()) return -1;
        window = glfwCreateWindow(windowWidth, windowHeight, "SoroS Physics Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Set window position so window spawns at the same place every time
    //Placed on the right so user can see the prompt to type number of sparks
    glfwSetWindowPos(window, 1080, 540 - (windowHeight / 2));

    //Create, start, then deconstruct game when finished
    Game game(window, windowWidth, windowHeight);
    game.start();
    game.~Game();

    return 0;
}
