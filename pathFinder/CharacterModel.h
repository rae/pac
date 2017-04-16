#ifndef CharacterModel_h
#define CharacterModel_h

#include "Node.h"

struct CharacterModel {
	Node * currentNode;
	Node * nextNode;
	double x;
	double y;
	double dx;
	double dy;

	// the next node we go to if nothing is changed. if findAuto is true, then
	// try to findan "automatic" next node in another direction if this isn't
	// a waypoint
	virtual void findNextNode(bool findAuto);

	// called if we are in awaypoint; base class does nothing
	virtual void reevaluatePath();
};

#endif /* CharacterModel_h */
