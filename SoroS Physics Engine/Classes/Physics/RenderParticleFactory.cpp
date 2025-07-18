#include "RenderParticleFactory.h"

using namespace Physics;

namespace Physics{
	// CONSTRUCTOR
	Physics::RenderParticleFactory::RenderParticleFactory(PhysicsWorld* physWorld)
	{
		generator.seed(random_device{}()); // feeds a seed into the randomizer
		physicsWorld = physWorld;
	}

	/*
	*	Creates the sphere model, physics particle, and the render particle to hold both.
	*		- Also adds the physics particle to the particle list in Game
	*		- Handles the randomized properties of the particle
	* 
	*	Used specifically for randomizing colors, sizes, and lifespan (like firework sparks)
	*/
	RenderParticle* Physics::RenderParticleFactory::create()
	{
		// MAKING THE SPHERE OBJECT // 
		Vector vecPos(0, -600, 0);
		float scale = randomizeFloat(minRadius, maxRadius); // Random scale
			Vector vecScale(scale, scale, scale);
		Vector vecRot(0, 0, 0);
		Vector vecColor(randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f)); // Random color
	
		Model3D* sphere = new Object(
			"3D/sphere.obj",
			(vec3)vecPos,
			(vec3)vecScale,
			(vec3)vecRot,
			"Shaders/ObjectShader.vert",
			"Shaders/ObjectShader.frag",
			(vec3)vecColor
		);

		// MAKING THE PARTICLE //
		Particle* particle = new Particle();

		particle->position = vecPos;
			// Randomizing the particle's initial velocity to imitate fountain firework effect
		Vector vel(randomizeFloat(-100.0f, 100.0f), randomizeFloat(100.f, 250.0f), randomizeFloat(-100.0f, 100.0f));
		particle->velocity = vel;
			// Random lifespan
		particle->lifespan = randomizeFloat(minLifespan, maxLifespan); 

			// Adding the particle to the physics world
		physicsWorld->addParticle(particle);

		// MAKING THE RENDER PARTICLE //
		RenderParticle* renPar = new RenderParticle(particle, sphere, vecColor);

		return renPar;
	}

	/*
	*	Creates the sphere model, physics particle, and the render particle to hold both.
	*		- Also adds the physics particle to the particle list in Game
	* 
	*	Used specifically for creating uniform particles (like the newton's cradle's balls)
	*/
	RenderParticle* RenderParticleFactory::create(Vector position, float scale, Vector color, Vector velocity, float lifespan)
	{
		// MAKING THE SPHERE OBJECT // 
		Vector vecScale(scale, scale, scale);
		Vector vecRot(0, 0, 0);

		Model3D* sphere = new Object(
			"3D/sphere.obj",
			(vec3)position,
			(vec3)vecScale,
			(vec3)vecRot,
			"Shaders/ObjectShader.vert",
			"Shaders/ObjectShader.frag",
			(vec3)color
		);

		// MAKING THE PARTICLE //
		Particle* particle = new Particle();
		particle->radius = scale;
		particle->position = position;
		particle->velocity = velocity;
		particle->lifespan = lifespan;

		// Adding the particle to the physics world
		physicsWorld->addParticle(particle);

		// MAKING THE RENDER PARTICLE //
		RenderParticle* renPar = new RenderParticle(particle, sphere, color);

		return renPar;
	}

	// HELPER FUNCION

	float Physics::RenderParticleFactory::randomizeFloat(float min, float max)
	{
		uniform_real_distribution<double> distribution(min, max);
		return distribution(generator);
	}
}