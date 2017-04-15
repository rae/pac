//
//  main.cpp
//  pathFinder
//
//  Created by Reid Ellis on 2017-04-14.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "Map.h"

const char *mapData[] = {
	"#######",
	"#*   *#",
	"# #####",
	"#*   *#",
	"#######"
};

const int mapRowCount = sizeof(mapData) / sizeof(mapData[0]);

int main(int argc, const char * argv[]) {
	Map * map = new Map;
	map->parseMap(mapData, mapRowCount);
	std::cout << "  0123456789" << std::endl;
	for(int y=0; y<map->height; y++) {
		std::cout << y << " ";
		for(int x=0; x<map->width; x++) {
			if(map->nodeAt(x, y)->canBePath) {
				std::cout << " ";
			} else {
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	// now try finding a path
	Node *start = map->nodeAt(5, 1);
	Node *finish = map->nodeAt(5, 3);
	NodeList *path = start->pathToNode(finish);
	std::cout << "Path from [" << start->x << "," << start->y << "] to [" << finish->x << "," << finish->y << "]:" << std::endl;
	for(Node *node : *path) {
		std::cout << "\t[" << node->x << "," << node->y << "]" << std::endl;
	}
	std::cout << "End of path." << std::endl;
	return 0;
}
