#include "ForceRegistry.h"

//using namespace Physics;

namespace Physics{
	void Physics::ForceRegistry::add(Particle* particle, ForceGenerator* generator) {
		ParticleForceRegistry toAdd;
		toAdd.particle = particle;
		toAdd.generator = generator;

		Registry.push_back(toAdd);
	}

	void Physics::ForceRegistry::remove(Particle* particle, ForceGenerator* generator) {
		Registry.remove_if(
			[particle, generator](ParticleForceRegistry reg) {
				return reg.particle == particle &&
					   reg.generator == generator;
			}
		);
	}

	void Physics::ForceRegistry::clear() {
		Registry.clear();
	}

	void Physics::ForceRegistry::updateForces(float time) {
		for (list<ParticleForceRegistry>::iterator i = Registry.begin();
			i != Registry.end();
			i++) {

			i->generator->updateForce(i->particle, time);
		}
	}
}