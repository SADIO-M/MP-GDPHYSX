#include "Orthographic.h"

//CONSTRUCTORS
Orthographic::Orthographic(){}
Orthographic::Orthographic(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	float left, float right, float bottom, float top):

	Camera(width, height, near, far, position, center) {

	leftPoint = left;
	rightPoint = right;
	bottomPoint = bottom;
	topPoint = top;
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

	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}