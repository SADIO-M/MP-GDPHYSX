#pragma once

#include "ForceGenerator.h"
/*
*	GravityForceGenerator class
*		- child of ForceGenerator
*		- Is a force generator for gravity specifically
*/
namespace Physics {
	class GravityForceGenerator : public ForceGenerator {
	private:
		//Gravity factor
		Vector gravity = Vector(0, -9.8f, 0);

	public:
		//CONSTRUCTOR
		GravityForceGenerator(const Vector grav);

		//FUNCTION
		void updateForce(Particle* particle, float time) override;
	};
}