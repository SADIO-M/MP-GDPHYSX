#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"

/*
	This is the Object class
		- This class is for more "general" objects
		- Define color when instantiating

	[Created by: Megan Sadio]
*/
class Object : public Model3D {
private:
	vec3 color;

public:
	//CONSTRUCTOR
	Object();
	Object(
		string pathName,
		vec3 pos, vec3 scale, vec3 rotate,
		string vertPath, string fragPath,
		vec3 color
	);

	//FUNCTIONS
	void loadObject();

	void update();
	void draw();

	vec3 getColor();
	void setColor(vec3 newColor);
};