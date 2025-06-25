#include "Camera.h"

//CONSTRUCTOR
Camera::Camera(){}
Camera::Camera(float width, float height,
	float near, float far,
	vec3 position, vec3 center,
	vec3 rotation) {

	windowWidth = width;
	windowHeight = height;

	zNear = near;
	zFar = far;

	cameraPosition = position;
	initialPosition = cameraPosition;
	cameraCenter = center;
	cameraRotation = rotation;
}

void Camera::rotateCamera()
{
	// Rotate the camera accordingly 
	rotationMatrix = rotate(identityMatrix, radians(cameraRotation.z), vec3(0, 0, 1));
	rotationMatrix = rotate(rotationMatrix, radians(cameraRotation.y), vec3(0, 1, 0));
	rotationMatrix = rotate(rotationMatrix, radians(cameraRotation.x), vec3(1, 0, 0));

	// Updates the camera's position from its rotation and its initial position
	//		- Saving this initial position is important especially for the Orthographic camera since it doesn't move
	//		- The perspective camera also needs its initial position for it to rotate properly
	cameraPosition = vec3(vec4(rotationMatrix * vec4(initialPosition, 1.0f)));
}

void Camera::checkCameraRotation() {
	if (cameraRotation.x > 81.0f) cameraRotation.x = 81.0f;
	if (cameraRotation.x < -81.0f) cameraRotation.x = -81.0f;
}

void Camera::rotateWithKeys(char keyPressed)
{
	switch (keyPressed) {
	case 'W': cameraRotation.x += rotateSpeed;
		break;
	case 'S': cameraRotation.x -= rotateSpeed;
		break;
	case 'A': cameraRotation.y -= rotateSpeed;
		break;
	case 'D': cameraRotation.y += rotateSpeed;
		break;
	}
}

void Camera::draw(GLuint shaderProg) {
	GLuint viewCamAddress = glGetUniformLocation(shaderProg, "camera_view");
	glUniformMatrix4fv(viewCamAddress, 1, GL_FALSE, value_ptr(viewMatrix));

	GLuint projectionAddress = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionAddress, 1, GL_FALSE, value_ptr(projectionMatrix));
}