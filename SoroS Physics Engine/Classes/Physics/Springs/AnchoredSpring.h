#pragma once

#include "../ForceGenerator.h"
#include "../Particle.h"
#include "../Vector.h"

/*
	AnchoredSpring class
		- Child of force generator
		- Has an anchor point, since it is linked to only one particle (from the anchor point)
		- Spring constant for bounciness, rest length for default length
*/
namespace Physics {
	class AnchoredSpring : public ForceGenerator {
	private: 
		Vector anchorPoint;
		float springConstant;
		float restLength;

	public:
		AnchoredSpring(Vector position, float springConst, float restLen);
		
		void updateForce(Particle* particle, float time) override;
	};
}