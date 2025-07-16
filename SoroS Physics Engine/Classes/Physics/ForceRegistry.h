#pragma once

#include <list>
#include "Particle.h"
#include "ForceGenerator.h"
#include "../../Config/namespace.h"

namespace Physics {
	class ForceRegistry {
	public: 
		void add(Particle* particle, ForceGenerator* generator);
		void remove(Particle* particle, ForceGenerator* generator);
		void clear();
		void updateForces(float time);

	protected:
		struct ParticleForceRegistry {
			Particle* particle;
			ForceGenerator* generator;
		};

		list<ParticleForceRegistry> Registry;
	};
}