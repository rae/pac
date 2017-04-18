//
//  Map.h
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include "SceneNode.h"
#include "PacMan.h"

class Node;

extern const float kMapScale;

struct Map : SceneNode {
	// constructor
	Map();

	virtual ~Map();

	static Map * sharedMap();

	// node access
	Node * nodeAt(int x, int y);

	// coordinate query
	bool contains(int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	// map population via ASCII strings
	void parseMap(const char *strings[], int rowCount);

	// draw all the SceneNodes that represent the map
	void draw(float scale);

	//
	// Node data
	//
	Node *** mapNodes; // yes, a triple-pointer

	PacMan *pacman;
	
	int height;
	int width;

private:
	void clearMap();
};
#endif /* Map_h */
