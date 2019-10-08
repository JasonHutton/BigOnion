#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
	: position()
	, rotation()
	, scale()
{
}

glm::mat4 Transform::toModelMatrix()
{
	glm::mat4 matrix = glm::mat4();

	// translation
	matrix = glm::translate(matrix, position.getGlmVec3());

	// rotation
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// scale
	matrix = glm::scale(matrix, scale.getGlmVec3());

	return matrix;
}
