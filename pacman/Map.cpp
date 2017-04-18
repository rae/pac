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
#include "Wall.h"
#include "PacMan.h"
#include "Ghost.h"

static Map* g_map = nullptr;

const float kMapScale = 0.06;

inline bool ispath(char c) { return c != '#'; }
inline bool iswall(char c) { return c == '#'; }
inline bool isghost(char c) { return c == '@'; }

Map::Map()
	: mapNodes(nullptr),
	height(0),
	width(0),
	SceneNode(mat4(1.0f), 1.0)
{
	g_map = this;
}

Map::~Map()
{
	clearMap();
}

Map* Map::sharedMap()
{
	return g_map;
}

void Map::parseMap(const char *strings[], int rowCount)
{
	// clear out existing map, if any
	clearMap();

	// sanity checks
	if(rowCount == 0 || strings == nullptr) {
		return;
	}

	vector<int> ghostPlaces;
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
	for(int y=0; y<height; y++)
	{
		// allocate an array of Node pointers and point the row pointer at them
		mapNodes[y] = new Node*[width];
		// validate the data
		assert(strings[y] != nullptr && strlen(strings[y]) == width);
		// create this row of nodes
		for(int x=0; x<width; x++)
		{
			mapNodes[y][x] = new Node(x, y, this);
			char mapChar = strings[y][x];
			// canBePath is true if the string has a space here
			mapNodes[y][x]->canBePath = ispath(mapChar);
			if (iswall(mapChar))
			{
				float xPos = x - (0.5*width);
				float yPos = y - (0.5*width);
				Wall * wall = new Wall(xPos*kMapScale, yPos*kMapScale, kMapScale);
				wall->gridMoveTo(x, y);
				wall->setColor(0, 0, 0.75);
				addChild(wall);
				mapNodes[y][x]->sceneNode = wall;
			}
			else
			{
				SceneNode* space = new SceneNode(x, y);
				mapNodes[y][x]->sceneNode = space;
				if (isghost(mapChar)) {
					ghostPlaces.push_back(x);
					ghostPlaces.push_back(y);
				}
			}
		}
	}

	pacMan = new PacMan(mat4(1.0f), kMapScale);
	pacMan->setColor(1.0, 1.0, 0.0);
	for (int i = 0; i < ghostPlaces.size(); i += 2) {
		Ghost * ghost = new Ghost(ghostPlaces[i], ghostPlaces[i + 1]);
		ghosts.push_back(ghost);
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
	// sanity checking
	if(mapNodes != nullptr && x >= 0 && x < width && y >= 0 && y < height) {
		node = mapNodes[y][x];
	}
	return node;
}

void Map::draw(float scale)
{
	//Step Four: Render My Children
	pacMan->render();
	for (SceneNode *node : children) {
		node->draw(scale);
	}
}
