#include "ParticleLink.h"

using namespace Physics;

namespace Physics{
	ParticleContact* Physics::ParticleLink::getContact()
	{
		return nullptr;
	}

	float Physics::ParticleLink::currentLength()
	{
		Vector currLength;
		if(particles[1] != nullptr) {
			currLength = particles[0]->position - particles[1]->position;
		}

		else {
						//Particle position		- Anchor Point position
			currLength = particles[0]->position - anchor;
		}

		return currLength.magnitude();
	}
	void ParticleLink::setAnchor(Vector anchor)
	{
		this->anchor = anchor;
	}
}