#pragma once

#include "../../Config/namespace.h"

namespace Physics{
	class Particle {
		//VARIABLES
		public:
			float lifespan = 5.0f; 
			float mass = 50.f;		 //Mass
			Vector position;		 //Current Pos
			Vector velocity;		 //Current Velocity
			Vector acceleration;	 //Current Acceleration
			float radius = 50.f;	 //Size of particle
			float restitution = 0.9f;//Bouncy and non-bouncy

		protected:
			//Default drag value
			float damping = 0.9f;
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

			//Checking
			bool atCenter();
	};
}