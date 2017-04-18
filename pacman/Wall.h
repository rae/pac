#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "SceneNode.h"

class Wall : public SceneNode
{
public:
	Wall(glm::mat4 transformation, float scale, float height);
	Wall(float x, float y, float scale);
	void draw(float scale) override;
	float height;
};
