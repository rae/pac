#include "Wall.h"

Wall::Wall(glm::mat4 aTransformation, float scale, float height)
: SceneNode(aTransformation, scale),
  height(height)
{
}

void Wall::draw(float scale)
{
	glBegin(GL_POLYGON);
	glVertex2f(-scale / 2, -height / 2);
	glVertex2f(scale / 2, -height / 2);
	glVertex2f(scale / 2, height / 2);
	glVertex2f(-scale / 2, height / 2);
	glEnd();
}
