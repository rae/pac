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
	"#     #",
	"#  ####",
	"#     #",
	"#######"
};

const int mapRowCount = sizeof(mapData) / sizeof(mapData[0]);

int main(int argc, const char * argv[]) {
	Map * map = new Map;
	map->parseMap(mapData, mapRowCount);
	for(int y=0; y<map->height; y++) {
		for(int x=0; x<map->width; x++) {
			if(map->nodeAt(x, y)->canBePath) {
				std::cout << " ";
			} else {
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	return 0;
}
