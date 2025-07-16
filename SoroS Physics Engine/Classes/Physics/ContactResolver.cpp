#include "ContactResolver.h"

using namespace Physics;

namespace Physics {
	ContactResolver::ContactResolver(unsigned maxIter)
	{
		maxIterations = maxIter;
	}

	void ContactResolver::resolveAllContacts(vector<ParticleContact*> contacts, float time) {
		for (currentIterations = 0; currentIterations <= maxIterations; currentIterations++) {
			// sorts
			sort(contacts.begin(), contacts.end(), [](ParticleContact* a, ParticleContact* b)
				-> bool {
					return a->separatingSpeed < b->separatingSpeed;
				});

			if(contacts[0]->separatingSpeed >= 0) {
				sort(contacts.begin(), contacts.end(), [](ParticleContact* a, ParticleContact* b)
					-> bool {
						return a->depth > b->depth;
					});
			}

			contacts[0]->resolve(time);

			// checks contacts
			if (contacts[0]->separatingSpeed >= 0 && contacts[0]->depth <= 0) return;
			
		}
	}
}