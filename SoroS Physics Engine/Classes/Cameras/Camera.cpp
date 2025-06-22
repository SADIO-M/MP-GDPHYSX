#include "Camera.h"

//CONSTRUCTOR
Camera::Camera(){}
Camera::Camera(float width, float height,
	float near, float far,
	vec3 position, vec3 center) {

	windowWidth = width;
	windowHeight = height;

	zNear = near;
	zFar = far;

	cameraPosition = position;
	cameraCenter = center;
}
