#include "PacMan.h"

PacMan::PacMan(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{
	initPacMan();
}

void PacMan::draw(float scale)
{
	glBegin(GL_POLYGON);
	glVertex2f(-scale / 2, -scale / 2);
	glVertex2f(scale / 2, -scale / 2);
	glVertex2f(scale / 2, scale / 2);
	glVertex2f(-scale / 2, scale / 2);
//	// 16 slices, 4 stacks
//	glutSolidSphere(scale, 16, 4);
	glEnd();
}

void PacMan::initPacMan()
{
	holdingUp = false;
	holdingDown = false;
	holdingLeft = false;
	holdingRight = false;

	gridX = 13;
	gridY = 11;

	position = glm::vec3(0.0, 0.0, 0.0);
	speed = glm::vec3(0.0, 0.0, 0.0);

	gridMoveTo(gridX, gridY);

	movementSpeedFactor = 0.5f;
}

void PacMan::update(float deltaTime)
{
	glm::vec3 movement;

	if (holdingUp)
	{
		movement.y += movementSpeedFactor;
	}

	if (holdingDown)
	{
		movement.y -= movementSpeedFactor;
	}

	if (holdingLeft)
	{
		movement.x -= movementSpeedFactor;
	}

	if (holdingRight)
	{
		movement.x += movementSpeedFactor;
	}

	double framerateIndependentFactor = movementSpeedFactor * deltaTime;
	movement *= framerateIndependentFactor;
	position += movement;
	translateBy(movement.x, movement.y);

	float myX, myY;
	getGridPositionFloat(myX, myY);
	printf("PacMan at [%g, %g]\n", myX, myY);
}
