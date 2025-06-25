#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Physics {
	class Vector {
	public:
		float x, y, z;

		//CONSTRUCTORS
		Vector();
		Vector(const float _x, const float _y, const float _z);
		explicit operator glm::vec3() const;

		//FUNCTIONS
			/* Magnitude and Direction */
		float magnitude();								
		Vector direction();								
			/* Basic Operations */
			// RHS stands for right-hand side
		Vector operator+ (const Vector RHS);	// Vector Addition
		Vector operator- (const Vector RHS);	// Vector Subtraction
		Vector operator* (const float scalar);	// Scalar Multiplication
		void operator+= (const Vector RHS);	    // Vector Addition (just with +=)
		void operator-= (const Vector RHS);		// Vector Subtraction (just with -=)
		void operator*= (const float scalar);   // Scalar Multiplication (just with *=)
			/* Vector Products */
		Vector component(const Vector RHS); //Component Product
		float dot(const Vector RHS);		//Dot Product
		Vector cross(const Vector RHS);		//Cross Product
	};
}