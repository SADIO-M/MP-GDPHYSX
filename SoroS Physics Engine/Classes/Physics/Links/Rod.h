#pragma once

#include "ParticleLink.h"

namespace Physics{
	class Rod : public ParticleLink {
	public:
		float rodLength = 1;
		float restitution = 0;
		
		ParticleContact* getContact() override;
	};
}