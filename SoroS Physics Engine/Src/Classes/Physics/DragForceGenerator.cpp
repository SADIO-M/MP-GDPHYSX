#include "DragForceGenerator.h"

using namespace Physics;

namespace Physics {
	//CONSTRUCTORS
	DragForceGenerator::DragForceGenerator() {}
	DragForceGenerator::DragForceGenerator(float newK1, float newK2){
		//To have a drag of specific coefficients
		k1 = newK1;
		k2 = newK2;
	}
	//FUNCTION
	void DragForceGenerator::updateForce(Particle* particle, float time){
		Vector force = Vector(0, 0, 0);
		//Get the current velocity of the particle
		Vector currVel = particle->velocity;
		
		//Get the current magnitude of the particle
		float magnitude = currVel.magnitude();
		//Do not apply drag if magnitude is negative or 0
		if (magnitude <= 0) return;

		//Else, apply drag (using the drag formula) on the particle
		float dragForce = (k1 * magnitude) + (k2 * magnitude);
		Vector direction = currVel.direction();
		particle->addForce(direction * -dragForce);
	}
}