#include "Particle.h"

using namespace Physics;

void Particle::updatePosition(float time) {
	this->position =
		this->position + (this->velocity * time) + ((this->acceleration * pow(time, 2)) * (1.0f/2.0f));
}

void Particle::updateVelocity(float time) {
	this->acceleration += accumulatedForce * (1.0f / mass);
	this->velocity = this->velocity + (this->acceleration * time);
	this->velocity = this->velocity * powf(damping, time);
}

void Particle::update(float time) {
	// Life maintenance
	lifespan -= time;
	if (lifespan <= 0) {
		Destroy();
		cout << "Destroying at lifespan = " << lifespan << endl;
	}

	this->updatePosition(time);
	this->updateVelocity(time);

	this->resetForce();
}

void Physics::Particle::addForce(Vector force)
{
	this->accumulatedForce += force;
}

void Physics::Particle::resetForce()
{
	this->accumulatedForce = Vector(0, 0, 0);
	this->acceleration = Vector(0, 0, 0);
}

void Particle::Destroy() {
	this->isDestroyed = true;
}

bool Particle::IsDestroyed() {
	return isDestroyed;
}

bool Particle::atCenter() {
	float distance = sqrt(
		pow((position.x - 0), 2) +
		pow((position.y - 0), 2) +
		pow((position.z - 0), 2)
	);

	if (distance < 1) return true;
	else return false;
}