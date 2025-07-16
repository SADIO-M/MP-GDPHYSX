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

		void addParticle(Particle* toAdd);
		//NEW
		void addStaticParticle(Particle* toAdd);

		void update(float time);

		list<Particle*>* getParticleList();
		Particle* getParticleAtIndex(int index);

		void changeGravity(float newGravity);

	private:
		GravityForceGenerator gravity = GravityForceGenerator(Vector(0, -50.0f, 0));
		void updateParticleList();

	protected:
		ContactResolver contactResolver = ContactResolver(10);
		void generateContacts();
		void getOverlaps();
	};
}