#include "RenderParticleFactory.h"

Physics::RenderParticleFactory::RenderParticleFactory(vector<Model3D*>* allModels, PhysicsWorld* physWorld)
{
	allGameModels = allModels;
	physicsWorld = physWorld;
}

RenderParticle* Physics::RenderParticleFactory::create()
{
	// make and push sphere into game's allModels vector
	Vector vecPos(0, -600, 0);
	float scale = randomizeFloat(minRadius, maxRadius);
	Vector vecScale(scale, scale, scale);
	Vector vecRot(0, 0, 0);
	Vector vecColor(randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f), randomizeFloat(0.0f, 1.0f));
	
	allGameModels->push_back(new Object(
		"3D/sphere.obj",
		(vec3)vecPos,
		(vec3)vecScale,
		(vec3)vecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)vecColor
	));

	// MAKING THE PARTILE //
	Particle* particle = new Particle();
	particle->position = vecPos;
	// [ TEMP ] assigning random initial velocity to particles so they shoot up
	Vector vel(randomizeFloat(-50.0f, 50.0f), randomizeFloat(50.f, 250.0f), randomizeFloat(-50.0f, 50.0f));
	particle->velocity = vel;
	particle->lifespan = randomizeFloat(minLifespan, maxLifespan);
	physicsWorld->addParticle(particle);

	RenderParticle* renPar = new RenderParticle(particle, allGameModels->back(), vecColor);

	return renPar;
}

// HELPER FUNCIONS

float Physics::RenderParticleFactory::randomizeFloat(float min, float max)
{
	uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}
