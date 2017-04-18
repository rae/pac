#include "Triangle.h"



Triangle::Triangle(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{

}

void Triangle::draw(float scale)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(-scale / 2, -scale / 3);
	glVertex2f(scale / 2, -scale / 2);
	glVertex2f(0, scale);
	glEnd();
}

