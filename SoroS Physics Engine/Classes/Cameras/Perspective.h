#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"

/*
	This is the Perspective class for the perspective camera
		- Contains all the variables needed for a perspective camera
		- Its main difference from the Orthographic camera is that it moves (rotates)
		- In the draw function, it makes its projection matrix = perspective(...)
		- Holds the field of view and rotation speed (since this camera rotates)
		- child of Camera

	[Created by: Megan Sadio]
*/

class Perspective : public Camera {
private:
	float fieldOfView;
	float rotateSpeed = 0.02f;

public:
	//CONSTRUCTORS
	Perspective();
	Perspective(float width, float height,
		float near, float far,
		vec3 position, vec3 center,
		vec3 rotation,
		float fov);

	//FUNCTIONS
	void rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos);
	//void rotateWithKeys(char keyPressed);

	void update();
	void draw(GLuint shaderProg);
};