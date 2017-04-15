//
//  Node.hpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <list>

struct Node;
struct Map;

typedef std::list<Node *> NodeList;

struct Node {
	// position of the node
	int x;
	int y;
	// false if a wall or blockage
	bool canBePath;

	//
	// current distance from the start / finish of the path
	//

	// "g"
	int srcDistance;
	// "h"
	int destDistance;

	// the previous node on the path before this one
	Node *parent;

	// which map does this node belong to?
	Map * map;

	//
	// methods
	//

	// trivial constructor sets x, y
	Node(int inX, int inY, Map *inMap);

	// "f"
	float totalCost() { return srcDistance + destDistance; }

	// calculate the distance, where diagonal costs 14 (~sqrt(2) * 10),
	// while stright costs 10 (1 * 10)
	int gridDistanceTo(Node * dest);

	// return a list of valid nodes surrounding this one
	NodeList * successors(Node *start, Node *finish);

	// search for a path to another node on "map" - returns nullptr for no path
	NodeList * pathToNode(Node *destination);

	// follow the parent nodes and generate a path
	NodeList * parentPath();

private:
	Node * findLeastCostNode(const NodeList &list);
};

#endif /* Node_hpp */
