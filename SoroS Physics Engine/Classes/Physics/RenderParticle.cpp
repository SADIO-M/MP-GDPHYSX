#include "RenderParticle.h"

RenderParticle::RenderParticle() {}

RenderParticle::RenderParticle(Particle* particle, Model3D* obj) {
	physicsParticle = particle;
	objectToRender = obj;
	color = Vector(1, 1, 1);
}

RenderParticle::RenderParticle(Particle* particle, Model3D* obj, Vector color) {
	physicsParticle = particle;
	objectToRender = obj;
	this->color = color;
}

void RenderParticle::draw() {
	Object* obj = dynamic_cast<Object*>(objectToRender);

	if (!physicsParticle->IsDestroyed()) {
		obj->setColor((vec3)color);
		obj->updatePos(physicsParticle->position);
		obj->draw();
	}

	// Sets the status of the render particle to destroyed if the particle has been destroyed
	else {
		isDestroyed = true;
	}
}