#include "RenderParticleFactory.h"

Physics::RenderParticleFactory::RenderParticleFactory(vector<Model3D*>* allModels, PhysicsWorld* physWorld)
{
	allGameModels = allModels;
	physicsWorld = physWorld;
}

RenderParticle* Physics::RenderParticleFactory::create()
{
	// make and push sphere into game's allModels vector
	Vector defaultPos(0, -600, 0);
	float scale = randomizeFloat(minRadius, maxRadius);
	Vector myVecScale(scale, scale, scale);
	Vector myVecRot(0, 0, 0);
	Vector color(randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f));
	
	allGameModels->push_back(new Object(
		"3D/sphere.obj",
		(vec3)defaultPos,
		(vec3)myVecScale,
		(vec3)myVecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)color
	));

	// MAKING THE PARTILE //
	Particle* particle = new Particle();
	particle->position = defaultPos;
	// [ TEMP ] assigning random initial velocity to particles so they shoot up
	Vector vel(randomizeFloat(-30.0f, 30.0f), randomizeFloat(1.0f, 100.0f), randomizeFloat(-30.0f, 30.0f));
	particle->velocity = vel;
	particle->lifespan = randomizeFloat(minLifespan, maxLifespan) * 5;
	physicsWorld->addParticle(particle);

	RenderParticle* renPar = new RenderParticle(particle, allGameModels->back(), color);

	return renPar;
}

// HELPER FUNCIONS

float Physics::RenderParticleFactory::randomizeFloat(float min, float max)
{
	uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}
