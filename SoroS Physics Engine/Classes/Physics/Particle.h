#pragma once

#include "../../Config/namespace.h"

/*
	Particle Class
		- Particle class, holds all of the information relevant for a particle to have
		- Has position, radius, mass, velocity, acceleration
		- Also has damping, lifespan, restitution 
		- Updates position and velocity of the particle
		- Adds and resets force applied onto particle
*/
namespace Physics{
	class Particle {
		//VARIABLES
		public:
			float lifespan = 5.0f;	 //Lifespan
			float mass = 50.f;		 //Mass
			Vector position;		 //Current Pos
			Vector velocity;		 //Current Velocity
			Vector acceleration;	 //Current Acceleration
			float radius = 50.f;	 //Size of particle
			float restitution = 0.9f;//Bouncy(1) and non-bouncy(0)

		protected:
			//Default drag value
			float damping = 0.9f;
			//Default state of particle
			bool isDestroyed = false;
			//Force before fixed update
			Vector accumulatedForce = Vector(0, 0, 0);

		//FUNCTIONS
		protected:
			void updatePosition(float time);
			void updateVelocity(float time);

		public:
			//Force-related
			void update(float time);
			void addForce(Vector force);
			void resetForce();

			//CHECKING
			void Destroy();
			bool IsDestroyed();
			bool atCenter();
	};
}