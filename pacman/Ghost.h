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
	void draw(float radius) override;
	int sides;
};
