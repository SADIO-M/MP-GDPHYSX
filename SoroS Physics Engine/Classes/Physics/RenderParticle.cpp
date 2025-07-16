#include "RenderParticle.h"

namespace Physics {
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
		obj->setScale(vec3(particle->radius));
	}

	void RenderParticle::draw() {
		Object* obj = dynamic_cast<Object*>(objectToRender);
		obj->setScale(vec3(physicsParticle->radius));

		if (!physicsParticle->IsDestroyed()) {
			obj->setColor((vec3)color);
			obj->updatePos(physicsParticle->position);
			obj->draw();
		}
	}
}