#pragma once

#include "ForceGenerator.h"

/*
	GravityForceGenerator class
		- Force generator for gravity
		- Simulates gravity applied on a particle by adding the downward force to it
*/
namespace Physics {
	class GravityForceGenerator : public ForceGenerator {
	private:
		Vector gravity = Vector(0, -9.8f, 0);

	public:
		GravityForceGenerator(const Vector grav);
		void updateForce(Particle* particle, float time) override;
	};
}