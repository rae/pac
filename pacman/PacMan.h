#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "SceneNode.h"

class PacMan : public SceneNode
{
protected:
	glm::vec3 speed;

	double movementSpeedFactor;

	void initPacMan();

public:
	glm::vec3 position;
	bool holdingUp;
	bool holdingDown;
	bool holdingLeft;
	bool holdingRight;

	PacMan(glm::mat4 transformation, float scale);
	void draw(float scale) override;
	void move(double deltaTime);
};
