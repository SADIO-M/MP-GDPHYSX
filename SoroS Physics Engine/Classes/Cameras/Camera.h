#pragma once
 
#include "../../Config/namespace.h"

/*
	Camera class that contains general camera information
		- Parent of Orthographic
*/
class Camera {
protected:
	float windowWidth;
	float windowHeight;

	mat4 viewMatrix;
	mat4 projectionMatrix;
	
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
	
	float zNear;
	float zFar;
	
	vec3 cameraPosition;
	vec3 cameraCenter;
public:
	//CONSTRUCTOR
	Camera();
	Camera(float width, float height,
		   float near,  float far,
		   vec3 position, vec3 center);
};