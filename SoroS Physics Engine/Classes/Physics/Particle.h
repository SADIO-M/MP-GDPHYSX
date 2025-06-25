#pragma once

#include "../../Config/namespace.h"

/*
*	Particle class
*		- The particle object
*		- Has mass, position, velocity, acceleration, and lifespan (if particle needs to be destroyed after a certain amt of time)
*		- Is affected by damping
*		- Use this class to create a particle that is also affected by forces
*/
namespace Physics{
	class Particle {
		//VARIABLES
		public:
			float mass = 1;			//Mass
			Vector position;		//Current Pos
			Vector velocity;		//Current Velocity
			Vector acceleration;	//Current Acceleration

			float lifespan = 5.0f;  //Default lifespan, just to make sure it doesn't go out of 1-10s

		protected:
			//Default drag value
			float damping = 0.9f;
			//Variable to check if particle is destroyed
			bool isDestroyed = false;
			//Force before fixed update
			Vector accumulatedForce = Vector(0, 0, 0);

		//FUNCTIONS
		protected:
			void updatePosition(float time);
			void updateVelocity(float time);

		public:
			void update(float time);
			void addForce(Vector force);
			void resetForce();

			void Destroy();
			bool IsDestroyed();
	};
}