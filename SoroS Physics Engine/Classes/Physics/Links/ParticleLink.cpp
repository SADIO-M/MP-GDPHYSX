#include "ParticleLink.h"

using namespace Physics;

namespace Physics{
	//Override
	ParticleContact* Physics::ParticleLink::getContact()
	{
		return nullptr;
	}

	//Calculate the current length of the link between the two connected things
	float Physics::ParticleLink::currentLength()
	{
		Vector currLength;

		//If the link is between two particles
		if(particles[1] != nullptr) {
			currLength = particles[0]->position - particles[1]->position;
		}
		//If the link is between a particle and an anchor
		else {
			currLength = particles[0]->position - anchor;
		}
		//Return the length between the two
		return currLength.magnitude();
	}

	//Sets the anchor position 
	void ParticleLink::setAnchor(Vector anchor)
	{
		this->anchor = anchor;
	}

	//Allows a line link to be drawn (assigns a line to the variable)
	void ParticleLink::createLineLink()
	{
		float vertices[6];
		
		//If link is between two particles
		if (particles[1] != nullptr) {
			vertices[0] = particles[0]->position.x;
			vertices[1] = particles[0]->position.y;
			vertices[2] = particles[0]->position.z;
			vertices[3] = particles[1]->position.x;
			vertices[4] = particles[1]->position.y;
			vertices[5] = particles[1]->position.z;
		}
		//If link is between particle and anchor point
		else {
			vertices[0] = anchor.x;
			vertices[1] = anchor.y;
			vertices[2] = anchor.z;
			vertices[3] = particles[0]->position.x;
			vertices[4] = particles[0]->position.y;
			vertices[5] = particles[0]->position.z;
		}
		
		//Line link to draw
		lineLink = new Line(
			vertices,
			"Shaders/LineShader.vert",
			"Shaders/LineShader.frag"
		);
	}

	//Fix line link (or fix the way it is rendered) by reassigning line vertices
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

		lineLink->reassignVertices(vertices);
	}
}