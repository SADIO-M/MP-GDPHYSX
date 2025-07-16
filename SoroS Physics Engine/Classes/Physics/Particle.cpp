#include "Particle.h"

using namespace Physics;

namespace Physics{
	//Updates position based on velocity, time, and acceleration
	void Particle::updatePosition(float time) {
		this->position =
			this->position + (this->velocity * time) + ((this->acceleration * pow(time, 2)) * (1.0f/2.0f));
	}

	//Updates velocity based on acceleration and current velocity
	void Particle::updateVelocity(float time) {
		this->acceleration += accumulatedForce * (1.0f / mass);
		this->velocity = this->velocity + (this->acceleration * time);
		this->velocity = this->velocity * powf(damping, time);
	}

	//Updates the particle
	void Particle::update(float time) {
		// Life maintenance
		lifespan -= time;
		// If lifespan depleted, destroy this particle
		if (lifespan <= 0) {
			Destroy();
		}

		//Updates position and velocity
		this->updatePosition(time);
		this->updateVelocity(time);
		//Resets the forces applied
		this->resetForce();
	}

	// Adds a force to this particle
	void Physics::Particle::addForce(Vector force)
	{
		this->accumulatedForce += force;
	}

	// Reset the force applied on this particle (for impulses)
	void Physics::Particle::resetForce()
	{
		this->accumulatedForce = Vector(0, 0, 0);
		this->acceleration = Vector(0, 0, 0);
	}

	// Destroys this particle
	void Particle::Destroy() {
		this->isDestroyed = true;
	}

	// Returns if particle is destroyed
	bool Particle::IsDestroyed() {
		return isDestroyed;
	}
}