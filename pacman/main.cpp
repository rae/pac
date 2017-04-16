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

const char *simpleData[] = {
	"#######",
	"#    S#",
	"# #####",
	"#    F#",
	"#######"
};
const int simpleRowCount = sizeof(simpleData) / sizeof(simpleData[0]);

const char *pacmanData[] = {
	//    123456789 123456789 1234567
	"############################", // 0
	"#            ##            #", // 1
	"# #### ##### ## ##### #### #", // 2
	"# #### ##### ## ##### #### #", // 3
	"# #### ##### ## ##### #### #", // 4
	"#                          #", // 5
	"# #### ## ######## ## #### #", // 6
	"# #### ## ######## ## #### #", // 7
	"#      ##    ##    ##      #", // 8
	"###### ##### ## ##### ######", // 9
	"###### ##### ## ##### ######", // 10
	"###### ##          ## ######", // 11
	"###### ## ######## ## ######", // 12
	"###### ## ######## ## ######", // 13
	"          ########          ", // 14
	"###### ## ######## ## ######", // 15
	"###### ## ######## ## ######", // 16
	"###### ##          ## ######", // 17
	"###### ## ######## ## ######", // 18
	"###### ## ######## ## ######", // 19
	"#            ##            #", // 20
	"# #### ##### ## ##### #### #", // 21
	"# #### ##### ## ##### #### #", // 22
	"#   ##                ##   #", // 23
	"### ## ## ######## ## ## ###", // 24
	"### ## ## ######## ## ## ###", // 25
	"#      ##    ##    ##      #", // 26
	"# ########## ## ########## #", // 27
	"# ########## ## ########## #", // 28
	"#                          #", // 29
	"############################"  // 30
									//    123456789 123456789 1234567
};
const int pacmanRowCount = sizeof(pacmanData) / sizeof(pacmanData[0]);

char ** asciiMap(Map * map);
void printAsciiMap(char ** asciiMap, int rowCount);
void overlayAsciiPath(NodeList *path, char **map);

int main(int argc, const char * argv[]) {
	Node * start = nullptr;
	Node * finish = nullptr;

	Map * simpleMap = new Map;
	simpleMap->parseMap(simpleData, simpleRowCount);
	char ** simpleMapStrings = asciiMap(simpleMap);
	// now try finding a path
	start = simpleMap->nodeAt(5, 1);
	finish = simpleMap->nodeAt(5, 3);
	NodeList *simplePath = start->pathToNode(finish);
	overlayAsciiPath(simplePath, simpleMapStrings);
	std::cout << std::endl << "Simple map" << std::endl << std::endl;
	printAsciiMap(simpleMapStrings, simpleMap->height);

	std::cout << std::endl << std::endl << std::endl << "Pac Man map" << std::endl << std::endl;
	Map * pacmanMap = new Map;
	pacmanMap->parseMap(pacmanData, pacmanRowCount);
	char ** pacmanMapStrings = asciiMap(pacmanMap);
	// now try finding a path
	start = pacmanMap->nodeAt(3, 1);
	finish = pacmanMap->nodeAt(25, 29);
	NodeList *pacmanPath = start->pathToNode(finish);
	overlayAsciiPath(pacmanPath, pacmanMapStrings);
	printAsciiMap(pacmanMapStrings, pacmanMap->height);

	return 0;
}

char ** asciiMap(Map * map)
{
	char **mapStrings = new char *[map->height];
	for(int y=0; y<map->height; y++) {
		mapStrings[y] = new char[map->width];
	}

	for(int y=0; y<map->height; y++) {
		for(int x=0; x<map->width; x++) {
			if(map->nodeAt(x, y)->canBePath) {
				mapStrings[y][x] = ' ';
			} else {
				mapStrings[y][x] = '#';
			}
		}
	}
	return mapStrings;
}

void overlayAsciiPath(NodeList *path, char **map)
{
	// mark the path on the ascii map
	for(Node *node : *path) {
		map[node->y][node->x] = '*';
	}
	return;
}

void printAsciiMap(char ** asciiMap, int rowCount)
{
	if(asciiMap == nullptr || asciiMap[0] == nullptr) {
		return;
	}
	size_t width = strlen(asciiMap[0]);
	// leave room for y labels
	std::cout << "   ";
	for(char x=0; x<width; x++) {
		if(x>0 && x%10 == 0) {
			std::cout << ' ';
		} else {
			std::cout << x % 10;
		}
	}
	std::cout << std::endl << std::endl;
	for(int y=0; y< rowCount; y++) {
		printf("%02d %s %02d\n", y, asciiMap[y], y);
	}
	// leave room for y labels
	std::cout << "   ";
	for(char x=0; x<width; x++) {
		std::cout << x % 10;
	}
	std::cout << std::endl;
	return;
}
