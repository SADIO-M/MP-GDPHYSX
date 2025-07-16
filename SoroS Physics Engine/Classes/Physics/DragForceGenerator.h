#pragma once

#include "ForceGenerator.h"
#include "../../Config/namespace.h"

/*
*	DragForceGenerator class
*		- child of ForceGenerator
*		- force generator for drag
*		- either has a default value, or the user can place specific coefficient of frictions to simulate different surfaces
*/
namespace Physics {
	class DragForceGenerator : public ForceGenerator {
	private:
		//Coefficient of frictions
			//If you want to simulate differnt surfaces, construct a drag force with two coefficients
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