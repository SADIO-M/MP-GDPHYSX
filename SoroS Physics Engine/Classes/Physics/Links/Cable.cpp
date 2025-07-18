#include "Cable.h"

using namespace Physics;

namespace Physics {
	Cable::Cable() {}

	Cable::Cable(float cableLength, Vector anchor)
	{
		this->cableLength = cableLength;
		this->anchor = anchor;
	}

	//Cable with specific restitution
	Cable::Cable(float cableLength, float restitution, Vector anchor)
	{
		this->cableLength = cableLength;
		this->restitution = restitution;
		this->anchor = anchor;
	}

	//Get contact for cable
	ParticleContact* Cable::getContact()
	{
		//Set anchor (for ParticleLink) to get proper current length
		setAnchor(anchor);
		float currLength = currentLength();

		//If current length is equal to cable length, return
		if (currLength == cableLength) { return nullptr; }

		ParticleContact* particleContact = new ParticleContact();
		particleContact->particles[0] = particles[0];

		//Get direction between the anchor and the particle
		Vector direction = anchor - particles[0]->position;
		direction.normalize();

		//If current length is greater than the cable length, fix it to not go beyond the cable's length
		if (currLength > cableLength) {
			particleContact->contactNormal = direction;
			particleContact->depth = currLength - cableLength;
		}
		
		particleContact->restitution = restitution;

		return particleContact;
	}
}