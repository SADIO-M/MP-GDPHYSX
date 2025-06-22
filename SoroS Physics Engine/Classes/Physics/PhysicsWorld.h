#pragma once

#include <list>
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "../../Config/namespace.h"

namespace Physics {
	class PhysicsWorld {
	public:
		ForceRegistry forceRegistry;

		list<Particle*> Particles;

		void addParticle(Particle* toAdd);

		void update(float time);

		list<Particle*>* getParticleList();
		Particle* getParticleAtIndex(int index);

	private:
		GravityForceGenerator gravity = GravityForceGenerator(Vector(0, -9.8f, 0));

		void updateParticleList();
	};
}