#include <glm/gtx/matrix_decompose.hpp>

#include "Wall.h"

Wall::Wall(glm::mat4 aTransformation, float scale, float height)
: SceneNode(aTransformation, scale),
  height(height)
{
}

Wall::Wall(float x, float y, float scale)
: SceneNode(translate(mat4(1.0f), vec3(x, y, 0)), scale),
  height(scale)
{
}

void Wall::draw(float scale)
{
	glBegin(GL_POLYGON);
	glVertex2f(-height / 2, -height / 2);
	glVertex2f(height / 2, -height / 2);
	glVertex2f(height / 2, height / 2);
	glVertex2f(-height / 2, height / 2);
	glEnd();
}
