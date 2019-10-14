#pragma once

#include "../utils/utils.h"
#include <glm/glm.hpp>

struct Transform
{
public:
	Transform();

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

	glm::mat4 toModelMatrix();
};
