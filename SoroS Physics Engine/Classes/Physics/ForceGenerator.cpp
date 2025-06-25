#include "ForceGenerator.h"

using namespace Physics;

//0 by default, define the addForce in child classes
namespace Physics{
	void Physics::ForceGenerator::updateForce(Particle* p, float time) {
		p->addForce(Vector(0, 0, 0));
	}
}
