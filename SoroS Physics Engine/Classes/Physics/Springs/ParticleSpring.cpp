#include "ParticleSpring.h"

using namespace Physics;

namespace Physics {
	ParticleSpring::ParticleSpring(Particle* particle, float springConst, float restLen)
	{
		otherParticle = particle;
		springConstant = springConst;
		restLength = restLen;
	}

	void ParticleSpring::updateForce(Particle* particle, float time)
	{
		Vector pos = particle->position;
		Vector force = pos - otherParticle->position;

		float magnitude = force.magnitude();

		float springForce = -springConstant * abs(magnitude - restLength);

		force.normalize();
		force *= springForce;

		particle->addForce(force);
	}
}