#include "Rectangle.h"



Rectangle::Rectangle(glm::mat4 aTransformation, float scale, float height) : SceneNode(aTransformation, scale)
{
	this->height = height;
}

void Rectangle::draw(float scale)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(-scale / 2, -height / 2);
	glVertex2f(scale / 2, -height / 2);
	glVertex2f(scale / 2, height / 2);
	glVertex2f(-scale / 2, height / 2);
	glEnd();
}


