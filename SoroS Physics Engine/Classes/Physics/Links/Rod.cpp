#include "Rod.h"

using namespace Physics;

namespace Physics {
	//Get the contact of the rod
	ParticleContact* Rod::getContact()
	{
		float currLength = currentLength();
		//If current length is the rod length, then return
		if (currLength == rodLength) { return nullptr; }

		ParticleContact* particleContact = new ParticleContact();
		particleContact->particles[0] = particles[0];
		particleContact->particles[1] = particles[1];

		Vector direction = particles[1]->position - particles[0]->position;
		direction.normalize();

		//If the current length is greater than or less than the rod length, fix it to return it to the rod's length (simulate the rod's rigidness)
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