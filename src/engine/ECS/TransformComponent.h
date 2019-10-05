#pragma once
#include "Component.h"

#include <glm\gtc\type_ptr.hpp>
#include "../utils/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject;

class TransformComponent :
	public Component
{
public:
	TransformComponent();

	Vector3f getPosition();
	void setPosition(Vector3f);

	// get axis rotation
	Vector3f getRotation();
	void setRotation(Vector3f);

	Vector3f getScale();
	void setScale(Vector3f);
	void setScale(float scale);

	glm::mat4 getModelMatrix();

private:
	Vector3f position;

	// axis rotation
	Vector3f rotation;
	Vector3f scale;

	bool hasRigidBody();
};

