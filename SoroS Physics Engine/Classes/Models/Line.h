#pragma once

#include "Model3D.h"
#include "../../Config/namespace.h"

class Line : public Model3D {
private:
	GLuint VAO;
	float verticesArray[6];
	float lineWidth = 1.0f;
	vec3 color = vec3(1.0f);

public:
	Line();
	Line(float* verticesArray, string vertPath, string fragPath);
	Line(float* verticesArray, float lineWidth, vec3 color,
		 string vertPath, string fragPath);

	void loadLine();

	void update();
	void reassignPoints(float* newVertices);
	void draw();
};