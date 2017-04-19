#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "SceneNode.h"

class Ghost : public SceneNode
{
public:
	Ghost(glm::mat4 transformation, float scale, int sides);
	Ghost(int gridx, int gridy);
	void draw(float radius) override;
	void update(float now);
	void calculateVelocity(float inX, float inY);
	bool inMiddleOfPath(float myX, float myY);
	int sides;
};
