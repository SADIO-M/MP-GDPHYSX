#pragma once

#include "../ForceGenerator.h"

/*
	ParticleSpring class
		- Child of ForceGenerator
		- Allows a "spring" link (simulate a spring)
		- Spring constant for bounciness
		- Rest length for default length of the spring
		- Linking a spring between two particles
*/
namespace Physics {
	class ParticleSpring : public ForceGenerator {
	private:
		Particle* otherParticle;
		float springConstant;
		float restLength;

	public:
		ParticleSpring(Particle* particle, float springConst, float restLen);
		void updateForce(Particle* particle, float time) override;
	};
}