#include "GravityForceGenerator.h"

using namespace Physics;

namespace Physics{
	//CONSTRUCTOR
	Physics::GravityForceGenerator::GravityForceGenerator(const Vector grav) {
		gravity = grav;
	}
	//FUNCTION
	void Physics::GravityForceGenerator::updateForce(Particle* particle, float time) {
		// Do not place force on a particle with a mass of negative or 0
		if (particle->mass <= 0) return;
		// Else, add force on that particle
		Vector force = gravity * particle->mass;
		particle->addForce(force);
	}
}
