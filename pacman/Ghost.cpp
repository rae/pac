#define _USE_MATH_DEFINES

#include <math.h>
#include <glm/glm.hpp>
#include "Ghost.h"
#include "Map.h"

using namespace glm;

Ghost::Ghost(glm::mat4 aTransformation, float scale, int sides) : SceneNode(aTransformation, scale)
{
	this->sides = sides;
}

Ghost::Ghost(int x, int y)
: SceneNode(x, y),
  sides(16)
{
	scale = kMapScale;
	Node * node = Map::sharedMap()->nodeAt(gridx, gridy);
	assert(node != nullptr);
	delete path;
	PacMan *pacman = Map::sharedMap()->pacman;
	Node * pacnode = Map::sharedMap()->nodeAt(pacman->gridx, pacman->gridy);
	assert(pacnode != nullptr);
	path = node->pathToNode(pacnode);
}

void Ghost::draw(float radius)
{
	glBegin(GL_POLYGON);
	GLfloat delta = (M_PI * 2) / sides;
	for (GLfloat i = -M_PI; i < M_PI; i += delta)
	{
		GLfloat x = sin(i);
		GLfloat y = cos(i);
		glVertex2f(radius * x, radius * y);
	}
	glEnd();
}
