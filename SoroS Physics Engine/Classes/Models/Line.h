#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"

/*
	Line class
		- For creating lines or "links" to draw (to show the cable, rod, etc. connections)
		- Has its own VAO, especially when drawing multiple lines that constantly change vertices
		- Has an adjustable line width and color, but set to width 1 and white color by default

	[Created by: Megan Sadio]
*/
class Line : public Model3D {
private:
	GLuint VAO;				 //Own VAO
	float verticesArray[6];  //Holds the vertices of the line [0-2] is vertex 1 [3-5] is vertex 2
	float lineWidth = 1.0f;  //Line width
	vec3 color = vec3(1.0f); //Color

public:
	//CONSTRUCTORS
	Line();
	Line(float* verticesArray, string vertPath, string fragPath);
	Line(float* verticesArray, float lineWidth, vec3 color,
		 string vertPath, string fragPath);

	//FUNCTIONS
	void loadLine();

	void update();
	void reassignVertices(float* newVertices);
	void draw();
};