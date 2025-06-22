#pragma once

// Header file with all the necessary includes, also for code readability

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef TINYOBJ_H
	#define TINYOBJ_H
	#define TINYOBJLOADER_IMPLEMENTATION
	#include "../../tiny_obj_loader.h"
#endif

#ifndef STB_H
	#define STB_H
	#include "../../stb_image.h"
#endif

#include <chrono>

#include "../Classes/Physics/Vector.h"

using namespace std;
using namespace glm;
using namespace tinyobj;
using namespace Physics;
using namespace chrono_literals;

constexpr chrono::nanoseconds timestep(16ms);
