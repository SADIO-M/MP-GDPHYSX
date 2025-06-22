#pragma once

#include "ForceGenerator.h"

namespace Physics {
	class GravityForceGenerator : public ForceGenerator {
	private:
		Vector gravity = Vector(0, -9.8f, 0);

	public:
		GravityForceGenerator(const Vector grav);
		void updateForce(Particle* particle, float time) override;
	};
}