#ifndef SCENENODE_HEADER
#define SCENENODE_HEADER

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GLUT/GLUT.h>

class SceneNode
{
	protected:
	std::vector<SceneNode*> children;
	SceneNode* parent;
	glm::mat4 transformation;
	float r, g, b;
	float scale;

	public:
		//Constructor
		SceneNode(glm::mat4 transformation, float scale);

		//Methods
		void addChild(SceneNode*);
		void setColor(float r, float g, float b);
		glm::mat4 getTransformationMatrix();
		std::vector<SceneNode*> getChildren();
		SceneNode* getParent();
		void setParent(SceneNode* p);
		void render();
		virtual void draw(float scale) = 0;
		void translateBy(float x, float y);
};
#endif // !SCENENODE_HEADER
