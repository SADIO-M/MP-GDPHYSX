#pragma once

#include "../../Models/Line.h"
#include "../ParticleContact.h"

namespace Physics {
	class ParticleLink {
	public:
		Particle* particles[2];
		Vector anchor = Vector(0, 0, 0);

		Line* lineLink = nullptr;

		virtual ParticleContact* getContact();
		virtual void createLineLink();
		virtual void fixLineLink();
	
	protected:
		float currentLength();
		void setAnchor(Vector anchor);
	};
}