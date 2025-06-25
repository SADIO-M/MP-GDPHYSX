#pragma once

#include "../../Config/namespace.h"

namespace Physics{
	class Particle {
		//VARIABLES
		public:
			float mass = 1;			//Mass
			Vector position;		//Current Pos
			Vector velocity;		//Current Velocity
			Vector acceleration;	//Current Acceleration

			float lifespan = 5.0f;

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
	};
}