#pragma once

#include "RenderParticle.h"
#include "PhysicsWorld.h"

namespace Physics {
	class RenderParticleFactory {
	private:
		default_random_engine generator;
		vector<Model3D*>* allGameModels;
		PhysicsWorld* physicsWorld;

		// Setting min and max of variables
		float minRadius = 2.0f;
		float maxRadius = 10.0f;
		float minLifespan = 1.0f;
		float maxLifespan = 10.0f;
	public:
		RenderParticleFactory(vector<Model3D*>* allModels, PhysicsWorld* physWorld);
		RenderParticle* create();

		// Helper Functions
		float randomizeFloat(float min, float max);
	};
}