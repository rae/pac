//
//  Wall.cpp
//  pacman
//
//  Created by Reid Ellis on 2017-04-16.
//  Copyright © 2017 Tnir Technologies. All rights reserved.
//

#include "Wall.h"

Wall::Wall(glm::mat4 aTransformation, float scale, float height)
: SceneNode(aTransformation, scale),
  height(height)
{
}

void Wall::draw(float scale)
{
	glBegin(GL_POLYGON);
	glVertex2f(-scale / 2, -scale / 2);
	glVertex2f(scale / 2, -scale / 2);
	glVertex2f(scale / 2, scale / 2);
	glVertex2f(-scale / 2, scale / 2);
	glEnd();
}
