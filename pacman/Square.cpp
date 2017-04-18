#include "Square.h"



Square::Square(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{

}

void Square::draw(float scale)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(-scale / 2, -scale / 2);
	glVertex2f(scale / 2, -scale / 2);
	glVertex2f(scale / 2, scale / 2);
	glVertex2f(-scale / 2, scale / 2);
	glEnd();
}


