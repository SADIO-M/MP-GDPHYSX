#include "Vector.h"

using namespace Physics;

namespace Physics{
	//CONSTRUCTORS
	Vector::Vector(){ x = 0, y = 0, z = 0; }

	Vector::Vector(const float _x, const float _y, const float _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector::operator glm::vec3() const { return glm::vec3(x, y, z); }

	//FUNCTIONS
		/* Magnitude and Direction */
	float Vector::magnitude() {
		return sqrt(
			pow(this->x, 2) +
			pow(this->y, 2) +
			pow(this->z, 2));
	}

	Vector Vector::direction() {
		float magnitude = Vector::magnitude();
	
		return Vector(
			this->x / magnitude, 
			this->y / magnitude,
			this->z / magnitude
		);
	}
		/* Basic Operations */
		///// Addition
	Vector Vector::operator+ (const Vector RHS) {
		return Vector(
			this->x + RHS.x, 
			this->y + RHS.y, 
			this->z + RHS.z
		);
	}
		///// Subtraction
	Vector Vector::operator- (const Vector RHS) {
		return Vector(
			this->x - RHS.x, 
			this->y - RHS.y, 
			this->z - RHS.z
		);
	}
		///// Scalar Multiplication
	Vector Vector::operator* (const float scalar) {
		return Vector(
			this->x * scalar,
			this->y * scalar,
			this->z * scalar
		);
	}
		///// Addition
	void Physics::Vector::operator+=(const Vector RHS)
	{
		this->x += RHS.x;
		this->y += RHS.y;
		this->z += RHS.z;
	}
		///// Subtraction
	void Physics::Vector::operator-=(const Vector RHS)
	{
		this->x -= RHS.x;
		this->y -= RHS.y;
		this->z -= RHS.z;
	}
		///// Scalar Multiplication
	void Physics::Vector::operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
	}
		/* Vector Products */
		///// Component Product
	Vector Vector::component (const Vector RHS) {
		return Vector(
			this->x * RHS.x, 
			this->y * RHS.y, 
			this->z * RHS.z
		);
	}
		///// Dot / Scalar Product
	float Vector::dot(const Vector RHS) {
		return
			(this->x * RHS.x) +
			(this->y * RHS.y) +
			(this->z * RHS.z);
	}
		///// Cross / Vector Product
	Vector Vector::cross(const Vector RHS) {
		return Vector(
			(this->y * RHS.z) - (this->z * RHS.y),
			(this->z * RHS.x) - (this->x * RHS.z),
			(this->x * RHS.y) - (this->y * RHS.x)
		);
	}
}