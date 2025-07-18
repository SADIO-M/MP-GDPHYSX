#pragma once

#include <algorithm>

#include "ParticleContact.h"
#include "../../Config/namespace.h"

/*
	ContactResolver class
		- Responsible for resolving all contacts between particles
		- Can set a max number of resolve iterations (to avoid continuously resolving the same contacts, especially if they keep touching)
*/
namespace Physics {
	class ContactResolver {
	public:
		unsigned maxIterations;

		ContactResolver(unsigned maxIter);
		void resolveAllContacts(vector<ParticleContact*> contacts, float time);
	
	protected:
		unsigned currentIterations = 0;
	};
}