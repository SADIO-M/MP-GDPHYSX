#pragma once

#include <list>
#include "Particle.h"
#include "ForceGenerator.h"
#include "../../Config/namespace.h"

/*
*	ForceRegistry class
*		- A registry for managing particles and the forces that affect it
*		- To make a particle affected by a force, use add, then use remove to do the opposite
*		- Updates forces in registry as well
*/
namespace Physics {
	class ForceRegistry {
	public: 
		//FUNCTIONS
		void add(Particle* particle, ForceGenerator* generator);
		void remove(Particle* particle, ForceGenerator* generator);
		void clear();
		void updateForces(float time);

	protected:
		//A struct to contain a particle and a force generator
		//Basically, this is what holds the particle and the force that the particle is affected by
		struct ParticleForceRegistry {
			Particle* particle;
			ForceGenerator* generator;
		};
		//A list of the particles & forces from the struct above
		list<ParticleForceRegistry> Registry;
	};
}