#pragma once

#include "Particle.h"
#include "../../Config/namespace.h"

/*
	ForceGenerator class
		- Parent class to force generators
		- Can be used to simulate forces like gravity, drag, etc.
*/
namespace Physics {
	class ForceGenerator {
	public:
		//Override depending on use / formula
		virtual void updateForce(Particle* p, float time);
	};
}