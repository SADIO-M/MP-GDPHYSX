#pragma once

#include <list>
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "../../Config/namespace.h"

/*
*	PhysicsWorld class
*		- Has a list of particles
*		- Has a force registry to know what forces affect what particles
*		- Responsible for updating particles
*/
namespace Physics {
	class PhysicsWorld {
	public:
		//VARIABLES
		 // Used to apply a force to a particle
		ForceRegistry forceRegistry;
		 // List of all particles
		list<Particle*> Particles;

		//FUNCTIONS
		void addParticle(Particle* toAdd);

		void update(float time);

		list<Particle*>* getParticleList();
		Particle* getParticleAtIndex(int index);

	private:
		 //Gravity factor
		GravityForceGenerator gravity = GravityForceGenerator(Vector(0, -9.8f, 0));

		void updateParticleList();
	};
}