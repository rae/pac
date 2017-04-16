#include "SceneNode.h"
///////////////////////////////////////////////////////////////////////
//
// SceneNode.cpp
//
///////////////////////////////////////////////////////////////////////
using namespace std;

#ifndef M_PI
#define M_PI 3.1415926f
#endif

#define DEGREES_PER_RADIAN (360.0 / (2*M_PI))

SceneNode::SceneNode(glm::mat4 aTransformation, float aScale)
{
	transformation = aTransformation;
	parent = nullptr;
	children = std::vector<SceneNode*>();
	scale = aScale;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

void SceneNode::setColor(float R, float G, float B)
{
	r = R;
	g = G;
	b = B;
}
void SceneNode::setParent(SceneNode* p)
{
	parent = p;
}

void SceneNode::addChild(SceneNode* child)
{
	children.push_back(child);
	(*child).setParent(this);

}

glm::mat4 SceneNode::getTransformationMatrix()
{
	return transformation;
}

std::vector<SceneNode*> SceneNode::getChildren()
{
	return children;
}
SceneNode* SceneNode::getParent()
{
	return parent;
}

void SceneNode::render()
{
	//Step One: getMyTransformation
	glm::mat4 transf = getTransformationMatrix();
	glm::vec3 myScale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transf, myScale, rotation, translation, skew, perspective);

	//Step Two: glPushMatrix(My Transformation)
	glPushMatrix();
	glTranslatef(translation.x, translation.y, translation.z);
	float sqrtOfW = sqrt(1 - rotation.w * rotation.w);
	glRotatef(DEGREES_PER_RADIAN * 2 * acos(rotation.w), rotation.x / sqrtOfW, rotation.y / sqrtOfW, rotation.z / sqrtOfW);


	//Step Three: Draw myself
	glColor3f(r, g, b);
	draw(scale);


	//Step Four: Render My Children
	for (int i = 0; i < children.size(); i++)
	{
		SceneNode* tmp = children.at(i);
		(*tmp).render();
	}

	//Final Step: glPopMatrix()
	glPopMatrix();

	return;

}

void SceneNode::translateBy(float x, float y)
{
	transformation = glm::translate(transformation, glm::vec3(x, y, 0));
}
