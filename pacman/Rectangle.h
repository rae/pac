#pragma once

#include "SceneNode.h"
#include "glm\glm.hpp"
#include <glm\gtx\matrix_decompose.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <vector>

class Rectangle : public SceneNode
{
public:
	Rectangle::Rectangle(glm::mat4 transformation, float scale, float height);
	void draw(float scale) override;
	float height;
};