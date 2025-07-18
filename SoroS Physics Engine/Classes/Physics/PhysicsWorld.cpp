#include "PhysicsWorld.h"

using namespace Physics;

namespace Physics {
	//Add a contact
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

	//Add a particle affected by gravity
	void PhysicsWorld::addParticle(Particle* toAdd) {
		Particles.push_back(toAdd);
		forceRegistry.add(toAdd, &gravity);
	}

	//Add a particle not affected by gravity
	void PhysicsWorld::addStaticParticle(Particle* toAdd)
	{
		Particles.push_back(toAdd);
	}

	//Get the particle list
	list<Particle*>* PhysicsWorld::getParticleList() {
		return &Particles;
	}

	//Update everything
	void PhysicsWorld::update(float time) {
		//Update the particle list
		updateParticleList();
		//Update forces
		forceRegistry.updateForces(time);
		//Update individual particles
		for (list<Particle*>::iterator p = Particles.begin(); p != Particles.end(); p++) {
			(*p)->update(time);
		}
		//Generate contacts (check if any contacts occurred)
		generateContacts();
		//If contacts occurred, resolve
		if (contacts.size() > 0) contactResolver.resolveAllContacts(contacts, time);
	}
	
	//Remove particle from list if destroyed
	void PhysicsWorld::updateParticleList() {
		Particles.remove_if(
			[](Particle* p) {
				return p->IsDestroyed();
			}
		);
	}

	//Get overlaps, if any
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

	//Clear contacts, check if there are any overlapping particles, then push back if contact is present
	void PhysicsWorld::generateContacts()
	{
		contacts.clear();
		getOverlaps();

		for (int i = 0; i < links.size(); i++) {
			ParticleContact* addContact = links[i]->getContact();
			if (addContact != nullptr) { contacts.push_back(addContact);}
		}
	}

	//Get a particle at a specific index
	Particle* PhysicsWorld::getParticleAtIndex(int index) {
		list<Particle*>::iterator particle = Particles.begin();
		advance(particle, index);
		return *particle;
	}

	//Return the links list 
	vector<ParticleLink*>* PhysicsWorld::getLinkList()
	{
		return &links;
	}

	//Get a link at a specific index
	ParticleLink* PhysicsWorld::getLinkAtIndex(int index)
	{
		return links[index];
	}

	//Change gravity
	void PhysicsWorld::changeGravity(float newGravity)
	{
		if (newGravity > 0) newGravity *= -1;

		gravity = GravityForceGenerator(Vector(0, newGravity, 0));
	}
}