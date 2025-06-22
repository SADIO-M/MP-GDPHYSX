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
	mat4 identityMatrix = mat4(1.0f);
	
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
	
	float zNear;
	float zFar;

	vec3 initialPosition;
	vec3 cameraPosition;
	vec3 cameraCenter;

	float rotateSpeed = 0.01f;
	vec3 cameraRotation = vec3(0.0f);
	mat4 rotationMatrix = mat4(1.0f);
	vec3 toLookAt = vec3(0.0f);
public:
	//CONSTRUCTOR
	Camera();
	Camera(float width, float height,
		   float near,  float far,
		   vec3 position, vec3 center,
		   vec3 rotation);

	virtual void rotateCamera();
	virtual void checkCameraRotation();
	virtual void rotateWithKeys(char keyPressed);

	virtual void update() = 0;
	virtual void draw(GLuint shaderProg) = 0;
};