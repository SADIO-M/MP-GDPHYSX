#include "ForceGenerator.h"

using namespace Physics;

namespace Physics {
	void Physics::ForceGenerator::updateForce(Particle* p, float time) {
		p->addForce(Vector(0, 0, 0));
	}
}