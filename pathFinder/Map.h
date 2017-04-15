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
	Node * nodeAt(int x, int y);

	bool contains(int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

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
