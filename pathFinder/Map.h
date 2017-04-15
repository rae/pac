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
	int width();
	int height();

	bool contains(int x, int y) {
		return x >= 0 && x < width() && y >= 0 && y < height();
	}
};
#endif /* Map_hpp */
