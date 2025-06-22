#pragma once

#include <fstream>
#include <sstream>
#include "../../Config/namespace.h"

/*	
	Shader class for all Shader-related operations
		- Loading file, creating, attaching, and linker shaders to shader program
        - Contains the shader program of the object
*/
class Shader {
private:
	//Holds the shader program
	GLuint shaderProg;
public:
	//CONSTRUCTOR
	Shader();

	//FUNCTION
	void createShader(string vertPath, string fragPath);

	//GETTER
	GLuint getShaderProg();
};