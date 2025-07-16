#include "Cable.h"

using namespace Physics;

namespace Physics {
	Cable::Cable() {}

	Cable::Cable(float cableLength, float restitution, Vector anchor)
	{
		this->cableLength = cableLength;
		this->restitution = restitution;
		this->anchor = anchor;
	}

	ParticleContact* Cable::getContact()
	{
		setAnchor(anchor);
		float currLength = currentLength();

		if (currLength == cableLength) { return nullptr; }

		ParticleContact* particleContact = new ParticleContact();
		particleContact->particles[0] = particles[0];
		//particleContact->particles[1] = particles[1];

		Vector direction = anchor - particles[0]->position;
		direction.normalize();

		if (currLength > cableLength) {
			particleContact->contactNormal = direction;
			particleContact->depth = currLength - cableLength;
		}
		
		particleContact->restitution = restitution;

		return particleContact;
	}
}