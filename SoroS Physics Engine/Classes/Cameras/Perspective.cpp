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

/*
	This function allows camera rotation with the keys (I, J, K, L)
*/
//void Perspective::rotateWithKeys(char keyPressed) {
//	switch (keyPressed) {
//		case 'W': cameraRotation.x += rotateSpeed;
//			break;
//		case 'S': cameraRotation.x -= rotateSpeed;
//			break;
//		case 'A': cameraRotation.y -= rotateSpeed;
//			break;
//		case 'D': cameraRotation.y += rotateSpeed;
//			break;
//	}
//}

/*
	This function checks the camera's rotation on the x-axis 
		- This is because when the x rotation goes over a certain threshold, the camera flips
		- This is to avoid that camera flipping for a cleaner experience
*/

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