#pragma once

#include <algorithm>

#include "ParticleContact.h"
#include "../../Config/namespace.h"

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