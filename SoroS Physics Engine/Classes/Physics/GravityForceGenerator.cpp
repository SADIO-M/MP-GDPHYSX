#include "GravityForceGenerator.h"

using namespace Physics;

namespace Physics{
	Physics::GravityForceGenerator::GravityForceGenerator(const Vector grav) {
		gravity = grav;
	}

	void Physics::GravityForceGenerator::updateForce(Particle* particle, float time) {
		//If particle's mass is 0 or negative, does not exist
		if (particle->mass <= 0) return;

		//Gravity formula
		Vector force = gravity * particle->mass;
		particle->addForce(force);
	}
}
