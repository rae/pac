//
//  Node.cpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#include <cmath>
#include <climits>
#include <cstdlib>

#include "Node.h"
#include "Map.h"

// used by pathToNode and successors
NodeList * openList = new NodeList;
NodeList * closedList = new NodeList;

inline int max(int a, int b)
{
	return a > b ? a : b;
}

//
// Based on a single node-to-node distance being 10,
// so the diagonal distance is sqrt(2)*10, which is pretty
// close to 14
//
const int kStraightDistance = 10;
const int diagonalDistance = 14;

int Node::gridDistanceTo(Node *dest)
{
	if(dest == nullptr) {
		return INT_MAX;
	}
	int dx = abs(dest->x - x);
	int dy = abs(dest->y - y);

	// the difference between dx and dy are how many diagonal moves are needed
	int diagonalCount = abs(dy - dx);
	// so the straight moves are the leftovers after all the diagonal moves are done
	int straightCount = max(dx, dy) - diagonalCount;
	return straightCount * kStraightDistance + diagonalCount * diagonalDistance;
}

NodeList * Node::successors(Node *start, Node *finish)
{
	NodeList * list = new NodeList;
	for(int dx=-1; dx < 2; dx++) {
		for(int dy=-1; dy < 2; dy++) {
			// skip ourself
			if(dx == 0 && dy == 0) {
				continue;
			}
			int newx = x+dx;
			int newy = y+dy;
			// skip coordinates outside the map
			if(!map->contains(newx, newy)) {
				continue;
			}
			Node *node = map->nodeAt(newx, newy);
			if(node == finish) {
				// found the finish node, so we are done!
				// get rid of anyone else in the list
				delete list;
				// create a new list consisting of the finish node
				list = new NodeList;
				list->push_back(node);
				// and return it
				return list;
			}
			// how to find out if a list contains a node
			bool nodeIsClosed = std::find(closedList->begin(), closedList->end(), node) == closedList->end();
			if(!node->canBePath || nodeIsClosed) {
				continue;
			}
			float g = node->gridDistanceTo(start);
			float h = node->gridDistanceTo(finish);
			int oldNodeCost = node->totalCost();
			// oldNodeCost == 0 means never checked
			if(oldNodeCost == 0 || g+h < oldNodeCost) {
				node->destDistance = h;
				node->srcDistance = g;
				node->parent = this;
			}
			list->push_back(node);
		}
	}
	return list;
}

NodeList * Node::pathToNode(Node *destination)
{
	return nullptr;
}
