///////////////////////////////////////////////////////////////////////
//
// SceneNode.cpp
//
///////////////////////////////////////////////////////////////////////

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneNode.h"
#include "Map.h"

using namespace std;
using namespace glm;

#ifndef M_PI
#define M_PI 3.1415926f
#endif

#define DEGREES_PER_RADIAN (360.0 / (2*M_PI))

SceneNode::SceneNode(mat4 aTransformation, float aScale)
{
	transformation = aTransformation;
	parent = nullptr;
	children = vector<SceneNode*>();
	scale = aScale;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	velocity.x = velocity.y = 0;
}

SceneNode::SceneNode(int x, int y)
	: transformation(glm::mat4(1.0f)), parent(nullptr), children(vector<SceneNode*>()), scale(1.0f), r(1.0f), g(1.0f), b(1.0f)
{
	gridX = x;
	gridY = y;
	gridMoveTo(gridX, gridY);
	velocity.x = velocity.y = 0;
}

SceneNode::~SceneNode()
{
	children.clear();
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
	child->setParent(this);
}

mat4 SceneNode::getTransformationMatrix()
{
	return transformation;
}

vector<SceneNode*> SceneNode::getChildren()
{
	return children;
}
SceneNode* SceneNode::getParent()
{
	return parent;
}

vec3 SceneNode::getScale()
{
	mat4 transf = getTransformationMatrix();
	vec3 myScale;
	quat rotation;
	vec3 translation;
	vec3 skew;
	vec4 perspective;
	decompose(transf, myScale, rotation, translation, skew, perspective);
	return myScale;
}

vec3 SceneNode::getTranslation()
{
	mat4 transf = getTransformationMatrix();
	vec3 myScale;
	quat rotation;
	vec3 translation;
	vec3 skew;
	vec4 perspective;
	decompose(transf, myScale, rotation, translation, skew, perspective);
	return translation;
}

void SceneNode::render()
{
	//Step One: getMyTransformation
	mat4 transf = getTransformationMatrix();
	vec3 myScale;
	quat rotation;
	vec3 translation;
	vec3 skew;
	vec4 perspective;
	decompose(transf, myScale, rotation, translation, skew, perspective);

	//Step Two: glPushMatrix(My Transformation)
	glPushMatrix();
	glTranslatef(translation.x, translation.y, translation.z);
	float sqrtOfW = sqrt(1 - rotation.w * rotation.w);
	glRotatef(DEGREES_PER_RADIAN * 2 * acos(rotation.w), rotation.x / sqrtOfW, rotation.y / sqrtOfW, rotation.z / sqrtOfW);

	//Step Three: Draw myself, a bit transparent
	glColor4f(r, g, b, 0.75);
	draw(scale);


	//Step Four: Render My Children
	for(SceneNode *node : children) {
		node->render();
	}

	//Final Step: glPopMatrix()
	glPopMatrix();

	return;

}

void SceneNode::translateBy(float x, float y)
{
	transformation = translate(transformation, vec3(x, y, 0));
}

void SceneNode::gridMoveTo(int x, int y)
{
	setGridPositionFloat(x, y);
}

void SceneNode::draw(float scale)
{
	return;
}

void SceneNode::update(float time_now)
{
	// do nothing
}

void SceneNode::getGridPositionFloat(float &gridXf, float &gridYf)
{
	vec3 rawPos = getTranslation();
	Map * map = Map::sharedMap();
	gridXf = rawPos.x / kMapScale + map->width / 2.0;
	gridYf = rawPos.y / kMapScale + map->height / 2.0;
}

void SceneNode::setGridPositionFloat(float gridXf, float gridYf)
{
	float mapWidth = Map::sharedMap()->width;
	float mapHeight = Map::sharedMap()->height;
	transformation = translate(glm::mat4(1.0f), vec3((gridXf - mapWidth / 2.0f)*kMapScale, (gridYf - mapHeight / 2.0f)*kMapScale, 0));
}
