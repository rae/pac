#ifndef SCENENODE_HEADER
#define SCENENODE_HEADER

#include <vector>

#ifdef __APPLE__
	#include <GLUT/GLUT.h>
#else
	#include <GL/GLUT.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Node.h"

using namespace glm;
using namespace std;

class SceneNode
{
protected:
	vector<SceneNode*> children;
	SceneNode* parent;
	mat4 transformation;
	float r, g, b;
	float scale;
	NodeList* path;

public:
	//Constructor
	SceneNode(glm::mat4 transformation, float scale);
	SceneNode(int x, int y);
	virtual ~SceneNode();

	//Methods
	void addChild(SceneNode*);
	void setColor(float r, float g, float b);
	glm::mat4 getTransformationMatrix();
	std::vector<SceneNode*> getChildren();
	SceneNode* getParent();
	void setParent(SceneNode* p);
	void render();

	vec3 getScale();
	vec3 getTranslation();
	void getGridPositionFloat(float &gridXf, float &gridYf);
	void setGridPositionFloat(float gridXf, float gridYf);

	virtual void draw(float scale);
	void translateBy(float x, float y);
	void gridMoveTo(int x, int y);
	void update(float time_now);

	int gridX, gridY;
	vec2 velocity;
};
#endif // !SCENENODE_HEADER
