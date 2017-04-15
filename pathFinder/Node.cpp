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
#include <algorithm>

#include "Node.h"
#include "Map.h"

// used by pathToNode and successors
NodeList * openList = new NodeList;
NodeList * closedList = new NodeList;

//
// Based on a single node-to-node distance being 10,
// so the diagonal distance is sqrt(2)*10, which is pretty
// close to 14
//
const int kStraightDistance = 10;
const int diagonalDistance = 14;

Node::Node(int inX, int inY, Map *inMap)
: x(inX),
  y(inY),
  canBePath(false),
  srcDistance(0),
  destDistance(0),
  parent(nullptr),
  map(inMap)
{
}

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
	int straightCount = std::max(dx, dy) - diagonalCount;
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

			if(!map->contains(newx, newy)) {
				// skip coordinates outside the map
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

			// destDistance
			int newDestDistance = node->gridDistanceTo(finish);

			// srcDistance is path distance to us + path distance to reach the neighbour node
			// assume straight
			int newSrcDistance = 10;
			if(dx != 0 && dy != 0) {
				// nope, it's a diagonal line
				newSrcDistance = 14;
			}
			// now add the path distance so far
			newSrcDistance += srcDistance;

			// check if this is the shortes path to this node
			int oldNodeCost = node->totalCost();
			int newTotalCost = newDestDistance + newSrcDistance;
			// oldNodeCost == 0 means never checked, newDestDistance+newSrcDistance would be new cost
			if(oldNodeCost == 0 || newTotalCost < oldNodeCost) {
				// update node since we are closer than any previous path
				node->srcDistance = newSrcDistance;
				node->destDistance = newDestDistance;
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
