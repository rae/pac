#include <cstdlib>
#include "CharacterModel.h"
#include "Map.h"

int sign(int num)
{
	return num/abs(num);
}

void CharacterModel::findNextNode(bool findAuto)
{
	// can't find a next node if we don't have a current one, and don't
	// need to if we've already found nextNode
	if(currentNode == nullptr || nextNode != nullptr) {
		return;
	}
	if(currentNode->isWaypoint()) {
		reevaluatePath();
	}
	int xinc = sign(dx);
	int yinc = sign(dy);
	nextNode = currentNode->map->nodeAt(x+xinc, y+yinc);
	if(nextNode == nullptr) {
		if(findAuto) {
			
		}
	}
}

void CharacterModel::reevaluatePath()
{
	// do nothing in base class
}
