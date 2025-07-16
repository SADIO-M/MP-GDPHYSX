#pragma once

#include "RenderParticle.h"
#include "PhysicsWorld.h"

/*
*	A "factory" to automatically create render particles.
*		- Made to simplify the creation of render particles so
*		  that less code needs to be repeated in Game.
* 
*	[ Created by: Yza Montuerto ]
*/
namespace Physics {
	class RenderParticleFactory {
	private:
		default_random_engine generator; // For randomization
		PhysicsWorld* physicsWorld; // A pointer to the physics world in Game

		// Setting min and max of variables
		float minRadius = 2.0f;
		float maxRadius = 10.0f;
		float minLifespan = 1.0f;
		float maxLifespan = 10.0f;
	public:
			// Recieves the VAR : [ physWorld ] from Game
		RenderParticleFactory(PhysicsWorld* physWorld);
			// Returns a pointer to the created render particle
		RenderParticle* create();
		RenderParticle* create(Vector position, float scale, Vector color, // Model info
							   Vector velocity, float lifespan);           // Particle info

		// Helper Function
		float randomizeFloat(float min, float max);
	};
}