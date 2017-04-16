//
//  Map.cpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#include <assert.h>
#include "Map.h"
#include "Node.h"

inline bool ispath(char c) { return c != '#'; }

void Map::parseMap(const char *strings[], int rowCount)
{
	// clear out existing map, if any
	clearMap();

	// sanity checks
	if(rowCount == 0 || strings == nullptr) {
		return;
	}

	//
	// about the mapNodes triple-pointer..
	//
	// each element of the map is a *pointer* to a Node, not a node itself,
	// so 3 levels of indirection are required.
	//
	// Maybe using a 'typedef Node *NodePtr;' would help make it clearer? Not sure.
	//

	// allocate the array of pointers which will point at the rows
	mapNodes = new Node**[rowCount];

	// assume all strings are the same width (verified with assert below)
	width = (int)strlen(strings[0]);
	height = rowCount;

	// populate the rows
	for(int y=0; y<height; y++) {
		// allocate an array of Node pointers and point the row pointer at them
		mapNodes[y] = new Node*[width];
		// validate the data
		assert(strings[y] != nullptr && strlen(strings[y]) == width);
		// create this row of nodes
		for(int x=0; x<width; x++) {
			mapNodes[y][x] = new Node(x, y, this);
			// canBePath is true if the string has a space here
			mapNodes[y][x]->canBePath = ispath(strings[y][x]);
		}
	}
}

void Map::clearMap()
{
	if(mapNodes == nullptr) {
		return;
	}
	for(int i=0; i<height; i++) {
		delete [] mapNodes[i];
	}
	delete mapNodes;
	mapNodes = nullptr;
}

Node * Map::nodeAt(int x, int y)
{
	Node * node = nullptr;
	// bounds checking
	if(x >= 0 && x < width && y >= 0 && y < height) {
		node = mapNodes[y][x];
	}
	return node;
}
