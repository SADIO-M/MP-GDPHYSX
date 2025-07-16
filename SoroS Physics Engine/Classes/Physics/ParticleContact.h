#pragma once

#include "Particle.h"
#include "../../Config/namespace.h"

namespace Physics {
	class ParticleContact {
	public:
		//VARIABLES
		Particle* particles[2];
		float restitution;
		Vector contactNormal;
		float depth;
		float separatingSpeed;
		
		//FUNCTION
		void resolve(float time);
		float getSeparatingSpeed();

	protected:
		void resolveVelocity(float time);
		void resolveInterpenetration(float time);
	};
}