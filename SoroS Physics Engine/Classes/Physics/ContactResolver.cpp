#include "ContactResolver.h"

using namespace Physics;

namespace Physics {
	//Set max number of iterations
	ContactResolver::ContactResolver(unsigned maxIter) {
		maxIterations = maxIter;
	}

	/*
	*	The algorithm used to resolve all the contacts in a given frame.
	*/
	void ContactResolver::resolveAllContacts(vector<ParticleContact*> contacts, float time) {
		for (currentIterations = 0; currentIterations <= maxIterations; currentIterations++) {
			// Sorts the contacts list in ascending order
			sort(contacts.begin(), contacts.end(), [](ParticleContact* a, ParticleContact* b)
				-> bool {
					return a->separatingSpeed < b->separatingSpeed;
				});

			// Checks if the first contact's separating speed is greater than zero. 
			// If it is, it will resort the contacts by depth
			if(contacts[0]->separatingSpeed >= 0) {
				sort(contacts.begin(), contacts.end(), [](ParticleContact* a, ParticleContact* b)
					-> bool {
						return a->depth > b->depth;
					});
			}

			// Resolves the first contact in the list, which will always be the correct one because of the previous sorting
			contacts[0]->resolve(time);

			// Checks if the first contact's SS is >= 0 or if its depth is <= 0
			// The first contact's status is indicative of the entire list since it is sorted
			// Breaks the loop if it is.
			if (contacts[0]->separatingSpeed >= 0 && contacts[0]->depth <= 0) return;
			
		}
	}
}