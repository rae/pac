#define _USE_MATH_DEFINES

#include <math.h>
#include "Ghost.h"
#include "Map.h"
#include "Node.h"
#include "PacMan.h"

static float kGhostSpeed = 0.0001;

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
	// get rid of first node
	path->pop_front();
	printf("Path ndoes for ghost %lx [%d, %d]:\n", unsigned long(this), x, y);
	for (Node *node : *path) {
		printf("\t [%d, %d]\n", node->x, node->y);
	}
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

void Ghost::calculateVelocity(float inX, float inY)
{
	velocity.x = 0;
	velocity.y = 0;
	if (path->size() == 0) {
		return;
	}
	Node * next = path->front();
	float dx = inX - next->x;
	float dy = inY - next->y;
	if (abs(dx) > abs(dy)) {
		velocity.x = kGhostSpeed * dx / abs(dx);
	}
	else {
		velocity.y = kGhostSpeed * dy / abs(dy);
	}
	printf("set velocity to [%g, %g]\n", velocity.x, velocity.y);
}

const float kFloatEpsilon = 0.01;

bool isBetween(float a, float middle, float b) {
	if (abs(a - middle) < kFloatEpsilon && abs(b - middle) < kFloatEpsilon) {
		return true;
	}
	return (a < middle && middle < b) || (b < middle && middle < a);
}

bool Ghost::inMiddleOfPath(float myX, float myY)
{
	if (path->size() == 0) {
		return false;
	}
	Node * next = path->front();
	bool isInMiddle = true;
	if (isBetween(myX, next->x, myX + velocity.x) || isBetween(myY, next->y, myY + velocity.y)) {
		printf("%d is between %g and %g, OR %d is between %g and %g\n",
			next->x, myX, myX + velocity.x, next->y, myY, myY + velocity.y);
		isInMiddle = false;
	}
	return isInMiddle;
}

void Ghost::update(float now)
{
	float myX, myY;
	if (path->size() == 0) {
		return;
	}
	getGridPositionFloat(myX, myY);
	Node *here = path->front();
	calculateVelocity(myX, myY);
	if (inMiddleOfPath(myX, myY)) {
		myX += velocity.x;
		myY += velocity.y;
		printf("ghost %lx - [%g, %g] -> [%d, %d] move by [%g, %g]\n", unsigned long(this), myX, myY, here->x, here->y, velocity.x, velocity.y);
		setGridPositionFloat(myX, myY);
	}
	else {
		path->pop_front();
		gridMoveTo(here->x, here->y);
	}
}
