//
//  Map.hpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

class Node;

struct Map {
	// constructor
	Map() : mapNodes(nullptr), height(0), width(0) {}

	// node access
	Node * nodeAt(int x, int y);

	// coordinate query
	bool contains(int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	// map population via ASCII strings
	void parseMap(const char *strings[], int rowCount);

	//
	// Node data
	//
	Node *** mapNodes; // yes, a triple-pointer
	int height;
	int width;

private:
	void clearMap();
};
#endif /* Map_hpp */
