#include "ParticleContact.h"

using namespace Physics;

namespace Physics {
	//Resolve velocity and interpenetration
	void ParticleContact::resolve(float time) {
		resolveVelocity(time);
		resolveInterpenetration(time);
	}

	//Get the separating speed of the particles
	float ParticleContact::getSeparatingSpeed() {
		Vector velocity = particles[0]->velocity;
		if (particles[1]) velocity -= particles[1]->velocity;
	
		separatingSpeed = velocity.dot(contactNormal);
		return separatingSpeed;
	}

	//Resolve the velocity of the particle (when they bump, how do they move)
	void ParticleContact::resolveVelocity(float time) {
		separatingSpeed = getSeparatingSpeed();

		if (separatingSpeed >= 0) return;

		float newSepaSpeed = -restitution * separatingSpeed;
		float deltaSpeed = newSepaSpeed - separatingSpeed;

		float totalMass = (float)1 / particles[0]->mass;
		if (particles[1]) totalMass += (float)1 / particles[1]->mass;
		//Invalid collision if mass is 0 or negative
		if (totalMass <= 0) return;

		float impulseMagnitude = deltaSpeed / totalMass;
		Vector impulse = contactNormal * impulseMagnitude;

		Vector particleAVelocity = impulse * ((float)1 / particles[0]->mass);
		particles[0]->velocity = particles[0]->velocity + particleAVelocity;

		if (particles[1]) {
			Vector particleBVelocity = impulse * ((float)-1 / particles[1]->mass);
			particles[1]->velocity = particles[1]->velocity + particleBVelocity;
		}
	}

	//Resolve interpenetration (when they overlap, how far should they go back)
	void ParticleContact::resolveInterpenetration(float time)
	{
		if (depth <= 0) return;

		float totalMass = (float)1 / particles[0]->mass;
		if (particles[1]) totalMass += (float)1 / particles[1]->mass;
		if (totalMass <= 0) return;

		float totalMoveByMass = depth / totalMass;
		Vector moveByMass = contactNormal * totalMoveByMass;

		Vector changeAPos = moveByMass * ((float)1 / particles[0]->mass);
		particles[0]->position += changeAPos;

		if (particles[1]) {
			Vector changeBPos = moveByMass * (-(float)1 / particles[1]->mass);
			particles[1]->position += changeBPos;
		}

		depth = 0;
	}
}