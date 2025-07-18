#pragma once

#include "Particle.h"
#include "../../Config/namespace.h"

/*
*	ParticleContact class
*		- Takes care of contacts between particles (resolves their velocity and interpenetration)
*/
namespace Physics {
	class ParticleContact {
	public:
		//VARIABLES
		Particle* particles[2];
		float restitution;
		Vector contactNormal;
		float depth;
		float separatingSpeed;
		
		//FUNCTIONS
		void resolve(float time);
		float getSeparatingSpeed();

	protected:
		void resolveVelocity(float time);
		void resolveInterpenetration(float time);
	};
}