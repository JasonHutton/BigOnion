#pragma once
#include "Component.h"
#include "../utils/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject;

class TransformComponent :
	public Component
{
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

	glm::mat4 getModelMatrix();

};

