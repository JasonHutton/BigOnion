#include "TransformComponent.h"

glm::mat4 TransformComponent::getModelMatrix() {

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position.getGlmVec3());

	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	return glm::scale(modelMatrix, scale.getGlmVec3());
}
