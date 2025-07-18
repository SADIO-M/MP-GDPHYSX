#pragma once

#include "ParticleLink.h"

/*
	Cable class
		- Create a cable that connects a particle and anchors it to a point in space
		- Has restitution for bounciness if ever
		- Cable length to know the max length
*/
namespace Physics {
	class Cable : public ParticleLink {
	public:
		float cableLength = 1;
		float restitution = 0.9;
		Vector anchor = Vector(0, 0, 0);

		Cable();
		Cable(float cableLength, Vector anchor); //To create default cable
		Cable(float cableLength, float restitution, Vector anchor); //To create cable with specific restitution
		ParticleContact* getContact() override;
	};
}