#pragma once

#include "ParticleLink.h"

/*
	Rod class
		- For particle link, creates a rod between two particles
		- Simulates a rod, so if two particles are connected by a rod, the distance between the two do not decrease or increase (fixed)
*/
namespace Physics{
	class Rod : public ParticleLink {
	public:
		float rodLength = 1;
		float restitution = 0;
		
		ParticleContact* getContact() override;
	};
}