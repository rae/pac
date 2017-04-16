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
#include <array>

#include "Node.h"
#include "Map.h"

// used by pathToNode and neighbours
NodeList * openList = new NodeList;
NodeList * closedList = new NodeList;

//
// Based on a single node-to-node distance being 10,
// so the diagonal distance is sqrt(2)*10, which is pretty
// close to 14
//
const int kDistanceStraight = 10;
const int kDistanceDiagonal = 14;

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

	// find dx, dy as the crow flies
	int dx = abs(dest->x - x);
	int dy = abs(dest->y - y);

	// the difference between dx and dy are how many diagonal moves are needed
	// note: this does *not* imply that players can move in diagonals
	int diagonalCount = abs(dy - dx);
	// so the straight moves are the leftovers after all the diagonal moves are done
	int straightCount = std::max(dx, dy) - diagonalCount;
	return straightCount * kDistanceStraight + diagonalCount * kDistanceDiagonal;
}

// Pac Man never moves on diagonals
#define OMIT_DIAGONALS 1

// convenience function - does this list contain this node?
bool contains(NodeList *list, Node *node)
{
	return std::find(list->begin(), list->end(), node) != list->end();
}

// use C++14 tuple to return a NodeList and a bool the NodeList is the list of neighbours,
// and the bool indicates whether the finish node was found, in which case the list has
// length 1 and only consists of the finish node.
//
std::tuple<NodeList *, bool> Node::neighbours(Node *finish)
{
	// the list of neighbours to return
	NodeList * neighbourList = new NodeList;
	bool foundFinish = false;

	// iterate over -1, 0, +1 in both x and y to cover all neighbouring nodes
	// (skipping 0,0 which is us)
	//
	int coords[] = { -1, 0, 1 };
	for(int dx : coords) {
		for(int dy : coords) {

			// skip ourself
			if(dx == 0 && dy == 0) {
				continue;
			}
#if OMIT_DIAGONALS
			if(abs(dx) == abs(dy)) {
				// skip diagonals
				continue;
			}
#endif
			int newx = x+dx;
			int newy = y+dy;

			Node *node = map->nodeAt(newx, newy);
			if(node == nullptr) {
				// probably coordinates outside the map
				// note: this is where we would handle wrap-around movement
				//       if we decide to do that.
				continue;
			}

			if(node == finish) {
				foundFinish = true;
				// found the finish node, so we are done!
				// get rid of anyone else in the neighbourList
				delete neighbourList;
				// create a new neighbourList consisting of the finish node
				neighbourList = new NodeList;
				neighbourList->push_back(node);
				// and return it along with the true 'foundFinish'
				return make_tuple(neighbourList, foundFinish);
			}

			bool nodeIsClosed = contains(closedList, node);
			bool nodeIsOpen = contains(openList, node);
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

			// oldNodeCost == 0 means never checked
			if(oldNodeCost == 0 || newTotalCost < oldNodeCost) {
				// update node since we are closer than any previous path
				node->srcDistance = newSrcDistance;
				node->destDistance = newDestDistance;
				node->parent = this;
			}
			if(!nodeIsOpen) {
				openList->push_back(node);
			}
			neighbourList->push_back(node);
		}
	}
	return make_tuple(neighbourList, foundFinish);
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
	NodeList* neighbours = nullptr;
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
		Node *cheapestNode = findLeastCostNode(*openList);
		openList->remove(cheapestNode);

		// get the neighbours around cheapestNode (which sets their parent to cheapestNode,
		// and adds them to the openList), checking if each is the destination
		std::tuple<NodeList *, bool> result = cheapestNode->neighbours(destination);

		// unpack the tuple
		neighbours = std::get<0>(result);
		bool foundDestination = std::get<1>(result);

		// check to see if the destination was a neighbour
		if(foundDestination) {
			destination->parent = cheapestNode;
			// return the built path tracking back through the 'parent' nodes (and reversing
			// the list to get start-to-finish)
			return destination->parentPath();
		}
		// add cheapestNode to the closed list since it's been checked out
		closedList->push_back(cheapestNode);
	}
	return path;
}

// returns path to this node by following the 'parent' nodes
NodeList * Node::parentPath()
{
	NodeList *path = new NodeList;
	Node *node = this;
	while(node->parent != nullptr) {
		path->push_back(node);
		node = node->parent;
	}
	// push back the final node, which is the start point
	path->push_back(node);
	// reverse the path so it goes from start to finish instead of finish to start
	path->reverse();
	return path;
}
