#include "RenderParticleFactory.h"

Physics::RenderParticleFactory::RenderParticleFactory(PhysicsWorld* physWorld)
{
	generator.seed(random_device{}());
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
	Vector vel(randomizeFloat(-100.0f, 100.0f), randomizeFloat(100.f, 250.0f), randomizeFloat(-50.0f, 50.0f));
	particle->velocity = vel;
	particle->lifespan = randomizeFloat(minLifespan, maxLifespan);
	physicsWorld->addParticle(particle);

	RenderParticle* renPar = new RenderParticle(particle, sphere, vecColor);

	return renPar;
}

// HELPER FUNCIONS

float Physics::RenderParticleFactory::randomizeFloat(float min, float max)
{
	uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}
