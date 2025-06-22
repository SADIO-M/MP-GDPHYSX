#include "GravityForceGenerator.h"

using namespace Physics;

namespace Physics{
	Physics::GravityForceGenerator::GravityForceGenerator(const Vector grav) {
		gravity = grav;
	}

	void Physics::GravityForceGenerator::updateForce(Particle* particle, float time) {
		if (particle->mass <= 0) return;

		Vector force = gravity * particle->mass;
		particle->addForce(force);
	}
}
