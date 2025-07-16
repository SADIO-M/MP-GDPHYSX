#include "Rod.h"

using namespace Physics;

namespace Physics {
	ParticleContact* Rod::getContact()
	{
		float currLength = currentLength();

		if (currLength == rodLength) { return nullptr; }

		ParticleContact* particleContact = new ParticleContact();
		particleContact->particles[0] = particles[0];
		particleContact->particles[1] = particles[1];

		Vector direction = particles[1]->position - particles[0]->position;
		direction.normalize();

		if (currLength > rodLength) {
			particleContact->contactNormal = direction;
			particleContact->depth = currLength - rodLength;
		}
		else {
			particleContact->contactNormal = direction * -1;
			particleContact->depth = rodLength - currLength;
		}

		particleContact->restitution = restitution;

		return particleContact;
	}
}