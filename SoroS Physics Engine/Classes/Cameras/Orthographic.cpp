#include "Orthographic.h"

//CONSTRUCTORS
Orthographic::Orthographic(){}
Orthographic::Orthographic(float width, float height,
	float near, float far,
	vec3 position, vec3 center, vec3 rotation,
	float left, float right, float bottom, float top):

	Camera(width, height, near, far, position, center, rotation) {

	leftPoint = left;
	rightPoint = right;
	bottomPoint = bottom;
	topPoint = top;
}

void Orthographic::update()
{
	rotateCamera();
	Camera::checkCameraRotation();
}

//FUNCTIONS
   //Draws the camera by assigning the view, projection, and sending that to the objects shader program
void Orthographic::draw(GLuint shaderProg) {
	viewMatrix = lookAt(cameraPosition, cameraCenter, worldUp);
	projectionMatrix = ortho(
		leftPoint,
		rightPoint,
		bottomPoint,
		topPoint,
		zNear,
		zFar);

	Camera::draw(shaderProg);
}