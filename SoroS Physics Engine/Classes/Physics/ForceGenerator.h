#pragma once

#include "Particle.h"
#include "../../Config/namespace.h"

/*
*	ForceGenerator class
*		- parent of forces like gravity and drag
*		- If you want to make a new force to apply to the particles, create a child class inherting from this class
*		- You can view DragForceGenerator.h or GravityForceGenerator.h as examples of this
*		- Do not forget to override updateForce, this is how the particle gets affected by this force
*		- NOTE: This class is for FORCES (applied constantly like gravity) and NOT IMPULSES
*/
namespace Physics {
	class ForceGenerator {
	public:
		//Override depending on use / formula of the force
			// Example, gravity is F = ma (force is equal to mass * acceleration)
		virtual void updateForce(Particle* p, float time);
	};
}