#pragma once

#include <list>
#include "Particle.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ParticleContact.h"
#include "ContactResolver.h"
#include "Links/ParticleLink.h"

#include "../../Config/namespace.h"

namespace Physics {
	class PhysicsWorld {
	public:
		ForceRegistry forceRegistry;

		vector<ParticleContact*> contacts;
		void addContact(Particle* p1, Particle* p2, float restitution, Vector contactNormal, float depth);

		vector<ParticleLink*> links;

		list<Particle*> Particles;

		// ADD PARTICLES
		void addParticle(Particle* toAdd);
		void addStaticParticle(Particle* toAdd);

		// UPDATE FUNCTION
		void update(float time);

		//SETTERS AND GETTERS
		list<Particle*>* getParticleList();
		Particle* getParticleAtIndex(int index);

		vector<ParticleLink*>* getLinkList();
		ParticleLink* getLinkAtIndex(int index);

		void changeGravity(float newGravity);

	private:
		GravityForceGenerator gravity = GravityForceGenerator(Vector(0, -9.8f, 0));
		void updateParticleList();

	protected:
		ContactResolver contactResolver = ContactResolver(10);
		void generateContacts();
		void getOverlaps();
	};
}