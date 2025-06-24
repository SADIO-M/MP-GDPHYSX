#include "PhysicsWorld.h"

using namespace Physics;

void PhysicsWorld::addParticle(Particle* toAdd) {
	Particles.push_back(toAdd);

	forceRegistry.add(toAdd, &gravity);
}

list<Particle*>* PhysicsWorld::getParticleList() {
	return &Particles;
}

void PhysicsWorld::update(float time){
	updateParticleList();

	forceRegistry.updateForces(time);

	for (list<Particle*>::iterator p = Particles.begin(); p != Particles.end(); p++){
		(*p)->update(time);
	}
}

void PhysicsWorld::updateParticleList() {
	Particles.remove_if(
		[](Particle* p) {
			return p->IsDestroyed();
		}
	);
}

Particle* PhysicsWorld::getParticleAtIndex(int index) {
	list<Particle*>::iterator particle = Particles.begin();
	advance(particle, index);
	return *particle;
}