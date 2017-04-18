#pragma once

#include "SceneNode.h"
#include "glm\glm.hpp"
#include <glm\gtx\matrix_decompose.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <vector>

class Circle : public SceneNode
{
public:
	Circle::Circle(glm::mat4 transformation, float scale, int sides);
	void draw(float radius) override;
	int sides;
};