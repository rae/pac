//
//  Map.cpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#include "Map.h"
#include "Node.h"

/////////////////////////////////////////////////////////////////
//
// data looks like this
//
const char *map[] = {
	"#######",
	"#     #",
	"#  ####",
	"#     #",
	"#######"
};

const int mapRowCount = sizeof(map) / sizeof(map[0]);

//
// end of data
//
/////////////////////////////////////////////////////////////////


void Map::parseMap(const char *strings[], int rowCount)
{
	if(mapNodes != nullptr) {
		clearMap();
	}
	// sanity checks
	if(rowCount == 0 || strings == nullptr) {
		return;
	}
	// allocate the array of pointers which will point at the rows
	mapNodes = new Node**[rowCount];

	// assume all strings are the same width
	width = (int)strlen(strings[0]);

	// populate the rows
	for(int y=0; y<rowCount; y++) {
		// allocate Nodes and point the row pointer at them
		mapNodes[y] = new Node*[width];
		for(int x=0; x<width; x++) {
			mapNodes[y][x] = new Node(x, y);
			mapNodes[y][x]->canBePath = (strings[y][x] == ' ');
		}
	}
}

void Map::clearMap()
{
	for(int i=0; i<height; i++) {
		delete [] mapNodes[i];
	}
	delete mapNodes;
	mapNodes = nullptr;
}

