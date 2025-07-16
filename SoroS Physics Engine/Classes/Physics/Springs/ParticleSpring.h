#pragma once

#include "../ForceGenerator.h"

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