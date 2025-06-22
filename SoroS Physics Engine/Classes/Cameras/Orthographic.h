#pragma once

#include "Camera.h"
#include "../../Config/namespace.h"

/*
	Orthographic camera class
		- Child of camera
		- Holds all relevant information for an orthographic projection
*/

class Orthographic : public Camera {
private:
	float leftPoint;
	float rightPoint;
	float bottomPoint;
	float topPoint;

public:
	//CONSTRUCTORS
	Orthographic();
	Orthographic(float width, float height,
				 float near, float far,
				 vec3 position, vec3 center, vec3 rotation,
			     float left, float right, float bottom, float top);

	//FUNCTIONS
	void update();
	void draw(GLuint shaderProg);
};