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

	void ParticleLink::createLineLink()
	{
		float vertices[6];
		
		if (particles[1] != nullptr) {
			vertices[0] = particles[0]->position.x;
			vertices[1] = particles[0]->position.y;
			vertices[2] = particles[0]->position.z;
			vertices[3] = particles[1]->position.x;
			vertices[4] = particles[1]->position.y;
			vertices[5] = particles[1]->position.z;
		}
		else {
			vertices[0] = anchor.x;
			vertices[1] = anchor.y;
			vertices[2] = anchor.z;
			vertices[3] = particles[0]->position.x;
			vertices[4] = particles[0]->position.y;
			vertices[5] = particles[0]->position.z;
		}
		
		lineLink = new Line(
			vertices,
			"Shaders/LineShader.vert",
			"Shaders/LineShader.frag"
		);
	}

	void ParticleLink::fixLineLink()
	{
		float vertices[6];

		if (particles[1] != nullptr) {
			vertices[0] = particles[0]->position.x;
			vertices[1] = particles[0]->position.y;
			vertices[2] = particles[0]->position.z;
			vertices[3] = particles[1]->position.x;
			vertices[4] = particles[1]->position.y;
			vertices[5] = particles[1]->position.z;
		}
		else {
			vertices[0] = anchor.x;
			vertices[1] = anchor.y;
			vertices[2] = anchor.z;
			vertices[3] = particles[0]->position.x;
			vertices[4] = particles[0]->position.y;
			vertices[5] = particles[0]->position.z;
		}

		lineLink->reassignPoints(vertices);
	}
}