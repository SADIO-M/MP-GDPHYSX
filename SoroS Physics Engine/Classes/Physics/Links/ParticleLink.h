#pragma once

#include "../../Models/Line.h"
#include "../ParticleContact.h"

/*
	ParticleLink class
		- For creating particle links
		- Has 2 particles (if user wants to connect two particles) or an anchor point
		- Has a lineLink to draw the line between the link (but will only draw if createLineLink is called when link is instantiated)
		- Also fixes the lineLink by reassigning vertices
*/
namespace Physics {
	class ParticleLink {
	public:
		Particle* particles[2];	//Two particles linked to each other (or just one then set the other to a nullptr)
		Vector anchor = Vector(0, 0, 0); //Anchor if ever

		Line* lineLink = nullptr; //Draw the link if ever

		//Get contact class, children should override
		virtual ParticleContact* getContact();
		
		virtual void createLineLink();
		virtual void fixLineLink();
	
	protected:
		float currentLength();
		void setAnchor(Vector anchor);
	};
}