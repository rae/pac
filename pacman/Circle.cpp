#define _USE_MATH_DEFINES

#include "Circle.h"
#include <math.h>



Circle::Circle(glm::mat4 aTransformation, float scale, int sides) : SceneNode(aTransformation, scale)
{
	this->sides = sides;
}

void Circle::draw(float radius)
{
	glBegin(GL_LINE_LOOP);
	GLfloat delta = (M_PI*2) / sides;
	for (GLfloat i = -M_PI; i < M_PI; i+= delta)
	{
		GLfloat x = sin(i);
		GLfloat y = cos(i);
		glVertex2f(radius * x, radius * y);
	}
	glEnd();
}
