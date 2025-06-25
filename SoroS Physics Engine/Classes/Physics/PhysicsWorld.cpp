#include "PhysicsWorld.h"

using namespace Physics;

namespace Physics{
	// Adds particle to list, also automatically registers it with gravity
	void PhysicsWorld::addParticle(Particle* toAdd) {
		Particles.push_back(toAdd);

		forceRegistry.add(toAdd, &gravity);
	}


	// Returns particle list
	list<Particle*>* PhysicsWorld::getParticleList() {
		return &Particles;
	}

	/*
	*	Updates the following things:
	*		- Calls the update for all particles in the list
	*		- Updates all the forces in the force registry
	*/
	void PhysicsWorld::update(float time){
		updateParticleList();

		forceRegistry.updateForces(time);

		for (list<Particle*>::iterator p = Particles.begin(); p != Particles.end(); p++){
			(*p)->update(time);
		}
	}

	// Updates all particles in the list, removes it if it is destroyed
	void PhysicsWorld::updateParticleList() {
		Particles.remove_if(
			[](Particle* p) {
				return p->IsDestroyed();
			}
		);
	}

	// Returns a particle at a certain index
	Particle* PhysicsWorld::getParticleAtIndex(int index) {
		list<Particle*>::iterator particle = Particles.begin();
		advance(particle, index);
		return *particle;
	}
}