#pragma once

#include "../ForceGenerator.h"
#include "../Particle.h"
#include "../Vector.h"

namespace Physics {
	class AnchoredSpring : public ForceGenerator {
	private: 
		Vector anchorPoint;
		float springConstant;
		float restLength;

	public:
		//CONSTRUCTOR
		AnchoredSpring(Vector position, float springConst, float restLen);
		
		void updateForce(Particle* particle, float time) override;
	};
}