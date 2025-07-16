#pragma once

#include "../ParticleContact.h"

namespace Physics {
	class ParticleLink {
	public:
		Particle* particles[2];
		Vector anchor = Vector(0, 0, 0);

		virtual ParticleContact* getContact();
	
	protected:
		float currentLength();
		void setAnchor(Vector anchor);
	};
}