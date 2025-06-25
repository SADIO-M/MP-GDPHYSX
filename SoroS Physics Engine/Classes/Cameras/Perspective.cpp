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
/*
	This rotateWithMouse handles the rotation using the mouse and calculates the rotation
		- Updates the camRotationMod, the modifier responsible for the camera's rotation
		- Gets the rotation from the previous mouse position and updates the current x and y accordingly
		- Rotate speed is for camera rotation sensitivity
*/
void Perspective::rotateWithMouse(dvec2* prevMousePos, dvec2* currMousePos) {
	cameraRotation.x -= (currMousePos->y - prevMousePos->y) * rotateSpeed;
	cameraRotation.y -= (prevMousePos->x - currMousePos->x) * rotateSpeed;

	prevMousePos->x = currMousePos->x;
	prevMousePos->y = currMousePos->y;
}

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