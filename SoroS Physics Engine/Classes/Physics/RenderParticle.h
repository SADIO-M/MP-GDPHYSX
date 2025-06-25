#pragma once

#include "Particle.h"
#include "Vector.h"
#include "../Models/Model3D.h"
#include "../Models/Object.h"
#include "../../Config/namespace.h"

namespace Physics {
	class RenderParticle {
	public:
		bool isDestroyed = false;
		Particle* physicsParticle;
		Model3D* objectToRender;
		Vector color;

		RenderParticle();
		RenderParticle(Particle* particle, Model3D* obj);
		RenderParticle(Particle* particle, Model3D* obj, Vector color);

		void draw();
	};
}