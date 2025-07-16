#pragma once

#include "Particle.h"
#include "../../Config/namespace.h"

namespace Physics {
	class ForceGenerator {
	public:
		//Override depending on use / formula
		virtual void updateForce(Particle* p, float time);
	};
}