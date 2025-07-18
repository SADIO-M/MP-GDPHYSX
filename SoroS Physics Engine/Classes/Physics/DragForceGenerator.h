#pragma once

#include "ForceGenerator.h"
#include "../../Config/namespace.h"

/*
	DragForceGenerator class
		- Simulates drag, has k1 and k2 that is modifiable to simulate different types of surfaces
*/
namespace Physics {
	class DragForceGenerator : public ForceGenerator {
	private:
		//Coefficient of frictions
		//Look up a table to know the friction coefficient of materials, these are arbitrary
		float k1 = 0.74f;
		float k2 = 0.57f;

	public:
		//CONSTRUCTORS
		DragForceGenerator();
		DragForceGenerator(float newK1, float newK2);

		//FUNCTIONS
		void updateForce(Particle* particle, float time) override;
	};
}