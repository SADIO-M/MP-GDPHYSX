#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"

/*
	Perspective camera
		- child of Camera
		- Contains all the variables needed for a perspective camera

	[Created by: Megan Sadio]
*/

class Perspective : public Camera {
private:
	float fieldOfView;

public:
	//CONSTRUCTORS
	Perspective();
	Perspective(float width, float height,
		float near, float far,
		vec3 position, vec3 center,
		vec3 rotation,
		float fov);

	//FUNCTIONS
	void update();
	void draw(GLuint shaderProg);
};