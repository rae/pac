#pragma once

#include "SceneNode.h"
#include "glm\glm.hpp"
#include <glm\gtx\matrix_decompose.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <vector>

class Triangle : public SceneNode
{
public:
	Triangle::Triangle(glm::mat4 transformation,  float scale);
	void draw(float scale) override;
};