#pragma once

#include "../utils/utils.h"
#include <glm/glm.hpp>

struct Transform
{
	Transform();

	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

};
