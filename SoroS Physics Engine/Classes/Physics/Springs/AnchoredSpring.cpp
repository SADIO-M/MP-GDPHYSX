#include "AnchoredSpring.h"

using namespace Physics;

namespace Physics{
	Physics::AnchoredSpring::AnchoredSpring(Vector position, float springConst, float restLen)
	{
		anchorPoint = position;
		springConstant = springConst;
		restLength = restLen;
	}

	void AnchoredSpring::updateForce(Particle* particle, float time)
	{
		Vector pos = particle->position;
		Vector force = pos - anchorPoint;

		float magnitude = force.magnitude();

		float springForce = -springConstant * abs(magnitude - restLength);
		
		force.normalize();
		force *= springForce;

		particle->addForce(force);
	}
}
