#include "DragForceGenerator.h"

using namespace Physics;

namespace Physics {
	DragForceGenerator::DragForceGenerator() {}
	DragForceGenerator::DragForceGenerator(float newK1, float newK2){
		k1 = newK1;
		k2 = newK2;
	}

	void DragForceGenerator::updateForce(Particle* particle, float time){
		Vector force = Vector(0, 0, 0);
		Vector currVel = particle->velocity;
		
		float magnitude = currVel.magnitude();
		if (magnitude <= 0) return;

		float dragForce = (k1 * magnitude) + (k2 * magnitude);
		Vector direction = currVel.direction();

		particle->addForce(direction * -dragForce);
	}
}