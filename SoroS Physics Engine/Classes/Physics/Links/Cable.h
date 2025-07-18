#pragma once

#include "ParticleLink.h"

namespace Physics {
	class Cable : public ParticleLink {
	public:
		float cableLength = 1;
		float restitution = 0.9;
		Vector anchor = Vector(0, 0, 0);

		Cable();
		Cable(float cableLength, Vector anchor);
		Cable(float cableLength, float restitution, Vector anchor);
		ParticleContact* getContact() override;
	};
}