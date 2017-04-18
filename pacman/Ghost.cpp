#define _USE_MATH_DEFINES

#include <math.h>
#include "Ghost.h"
#include "Map.h"
#include "Node.h"
#include "PacMan.h"

Ghost::Ghost(glm::mat4 aTransformation, float scale, int sides) : SceneNode(aTransformation, scale)
{
	this->sides = sides;
}

Ghost::Ghost(int x, int y)
	: SceneNode(x, y), sides(16)
{
	scale = kMapScale;
	Node* node = Map::sharedMap()->nodeAt(x, y);
	assert(node != nullptr);
	delete(path);
	PacMan* pacMan = Map::sharedMap()->pacMan;
	Node* pacNode = Map::sharedMap()->nodeAt(pacMan->gridX, pacMan->gridY);
	assert(pacNode != nullptr);
	path = node->pathToNode(pacNode);
}

void Ghost::draw(float radius)
{
	glBegin(GL_POLYGON);
	GLfloat delta = (M_PI * 2) / sides;
	for (GLfloat i = -M_PI; i < M_PI; i += delta)
	{
		GLfloat x = sin(i);
		GLfloat y = cos(i);
		glVertex2f((radius/2) * x, (radius/2) * y);
	}
	glEnd();
}
