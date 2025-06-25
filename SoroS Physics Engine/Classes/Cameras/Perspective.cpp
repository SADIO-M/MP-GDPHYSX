#include "Perspective.h"

//CONSTRUCTORS
Perspective::Perspective(){}

Perspective::Perspective(float width, float height,
						float near, float far,
						vec3 position, vec3 center,
						vec3 rotation,
						float fov) :

	Camera(width, height, near, far, position, center, rotation) {

	fieldOfView = fov;
}

//FUNCTIONS

void Perspective::update()
{
	rotateCamera();
	Camera::checkCameraRotation();
}

/*
	This function draws the perspective camera, it is similar to the Orthographic's draw function, 
		except the projectionMatrix = perspective()
*/
void Perspective::draw(GLuint shaderProg) {
	viewMatrix = lookAt(cameraPosition, toLookAt, worldUp);

	projectionMatrix = perspective(
		radians(fieldOfView),
		windowHeight / windowWidth,
		zNear,
		zFar);

	Camera::draw(shaderProg);
}