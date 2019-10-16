#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform()
	: position()
	, rotation()
	, scale()
{
}

/*
	Converts this Transform to a glm::mat4 transformation matrix For use in graphics.
*/
glm::mat4 Transform::toModelMatrix()
{
	glm::mat4 matrix = glm::mat4(1.0);

	// translation
	matrix = glm::translate(matrix, position.getGlmVec3());

	// rotation
	glm::mat4 rotationalMatrix = glm::eulerAngleZYX(rotation.z, rotation.y, rotation.x);
	matrix = matrix * rotationalMatrix;

	// scale
	matrix = glm::scale(matrix, scale.getGlmVec3());

	return matrix;
}
