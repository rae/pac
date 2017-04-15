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

NodeList * Node::successors(Node *finish)
{
	NodeList * list = new NodeList;
	// iterate from -1..+1 in x and y to cover all neighbouring nodes
	for(int dx=-1; dx < 2; dx++) {
		for(int dy=-1; dy < 2; dy++) {
			// skip ourself
			if(dx == 0 && dy == 0) {
				continue;
			}
			int newx = x+dx;
			int newy = y+dy;

			Node *node = map->nodeAt(newx, newy);
			if(node == nullptr) {
				// probably coordinates outside the map
				continue;
			}

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
			bool nodeIsClosed = std::find(closedList->begin(), closedList->end(), node) != closedList->end();
			bool nodeIsOpen = std::find(openList->begin(), openList->end(), node) != openList->end();
			// if it's a wall or on the closed list, skip this node
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
			if(!nodeIsOpen) {
				openList->push_back(node);
			}
			list->push_back(node);
		}
	}
	return list;
}

Node * Node::findLeastCostNode(const NodeList &list)
{
	Node * cheapest = nullptr;
	// use C++11's cool iteration syntax
	for(Node * node: list) {
		if(cheapest == nullptr || node->totalCost() < cheapest->totalCost()) {
			cheapest = node;
		}
	}
	return cheapest;
}

NodeList * Node::pathToNode(Node *destination)
{
	NodeList* successors = nullptr;
	NodeList* path = nullptr;

	// clear out old lists
	openList->clear();
	closedList->clear();

	// starting from here, so no distance from start
	srcDistance = 0;
	destDistance = gridDistanceTo(destination);

	// check trivial "found" case
	if(destination == this) {
		path = new NodeList;
		path->push_back(this);
		return path;
	}

	openList->push_back(this);
	while(!openList->empty()) {
		// get the next node with the least cost and remove it from the open list
		Node *q = findLeastCostNode(*openList);
		openList->remove(q);
		// get the successors around q (which sets their parent to q, and adds them to the openList),
		// checking if each is the destination
		successors = q->successors(destination);
		// check for found state
		if(successors->size() == 1 && successors->front() == destination) {
			destination->parent = q;
			return destination->parentPath();
		}
		// add q to the closed list since it's been checked out
		closedList->push_back(q);
	}
	return path;
}

// returns path from destination back to source (you may want to reverse this)
NodeList * Node::parentPath()
{
	NodeList *path = new NodeList;
	Node *node = this;
	while(node->parent != nullptr) {
		path->push_back(node);
		node = node->parent;
	}
	return path;
}
