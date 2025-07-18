#include "PhysicsWorld.h"

using namespace Physics;

namespace Physics {
	void PhysicsWorld::addContact(Particle* p1, Particle* p2, float restitution, Vector contactNormal, float depth)
	{
		ParticleContact* toAdd = new ParticleContact();

		toAdd->particles[0] = p1;
		toAdd->particles[1] = p2;
		toAdd->restitution = restitution;
		toAdd->contactNormal = contactNormal;
		toAdd->depth = depth;
	
		contacts.push_back(toAdd);
	}

	void PhysicsWorld::addParticle(Particle* toAdd) {
		Particles.push_back(toAdd);
		forceRegistry.add(toAdd, &gravity);
	}

	void PhysicsWorld::addStaticParticle(Particle* toAdd)
	{
		Particles.push_back(toAdd);
	}

	list<Particle*>* PhysicsWorld::getParticleList() {
		return &Particles;
	}

	void PhysicsWorld::update(float time) {
		updateParticleList();

		forceRegistry.updateForces(time);

		for (list<Particle*>::iterator p = Particles.begin(); p != Particles.end(); p++) {
			(*p)->update(time);
		}

		generateContacts();
		
		if (contacts.size() > 0) contactResolver.resolveAllContacts(contacts, time);
	}

	void PhysicsWorld::updateParticleList() {
		Particles.remove_if(
			[](Particle* p) {
				return p->IsDestroyed();
			}
		);
	}

	void PhysicsWorld::getOverlaps()
	{
		for (int i = 0; i < Particles.size() - 1; i++) {
			list<Particle*>::iterator a = next(Particles.begin(), i);

			for (int h = i + 1; h < Particles.size(); h++) {
				list<Particle*>::iterator b = next(Particles.begin(), h);

				Vector magSqrVector = (*a)->position - (*b)->position;

				float sqrMagnitude = magSqrVector.sqrMagnitude();

				float radius = (*a)->radius + (*b)->radius;
				float radiusSqr = radius * radius;

				//For overlapping and touching
				if(sqrMagnitude <= radiusSqr) {
					//Generate a contact
					Vector direction = magSqrVector.direction();
					float r = radiusSqr - sqrMagnitude;
					float depth = sqrt(r);

					float restitution = fmin((*a)->restitution, (*b)->restitution);
				
					addContact(*a, *b, restitution, direction, depth);
				}
			}
		}
	}

	void PhysicsWorld::generateContacts()
	{
		contacts.clear();
		getOverlaps();

		for (int i = 0; i < links.size(); i++) {
			ParticleContact* addContact = links[i]->getContact();
			if (addContact != nullptr) { contacts.push_back(addContact);}
		}
	}

	Particle* PhysicsWorld::getParticleAtIndex(int index) {
		list<Particle*>::iterator particle = Particles.begin();
		advance(particle, index);
		return *particle;
	}

	vector<ParticleLink*>* PhysicsWorld::getLinkList()
	{
		return &links;
	}

	ParticleLink* PhysicsWorld::getLinkAtIndex(int index)
	{
		return links[index];
	}

	void PhysicsWorld::changeGravity(float newGravity)
	{
		if (newGravity > 0) newGravity *= -1;

		gravity = GravityForceGenerator(Vector(0, newGravity, 0));
	}
}