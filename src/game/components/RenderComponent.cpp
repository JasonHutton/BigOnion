#include "RenderComponent.h"
#include "../../engine/utils/Vector3.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/BOEngine.h"
#include <glm\gtx\euler_angles.hpp>

const std::string RenderComponent::typeID = "Render";

RenderComponent::RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader)
	: model(modelPath, shader)
	, engine(engine)
{
	engine->addRenderComponent(this);
	ignorePause = true;
}

RenderComponent::~RenderComponent()
{
	engine->removeRenderComponent(this);
}


/*
	Converts this Transform to a glm::mat4 transformation matrix For use in graphics.
*/
glm::mat4 RenderComponent::toModelMatrix()
{
	Vector3f position = gameObject->transform.position;
	Vector3f rotation = gameObject->transform.rotation;
	Vector3f scale = gameObject->transform.scale;

	glm::mat4 matrix = glm::mat4(1.0);
	if (gameObject->parent) {
		RenderComponent* parentRender = gameObject->parent->getComponent<RenderComponent>();
		matrix = parentRender->toModelMatrix();
	}

	// translation
	matrix = glm::translate(matrix, position.getGlmVec3());

	// rotation
	glm::mat4 rotationalMatrix = glm::mat4(1.0);

	if (isSelfRotation) {
		rotationalMatrix = glm::rotate(rotationalMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));   //X
		rotationalMatrix = glm::rotate(rotationalMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));   //Y
		rotationalMatrix = glm::rotate(rotationalMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));   //Z
	}
	else {
		rotationalMatrix = glm::eulerAngleZYX(rotation.z, rotation.y, rotation.x);
	}

	matrix = matrix * rotationalMatrix;

	// scale
	matrix = glm::scale(matrix, scale.getGlmVec3());

	return matrix;
}

void RenderComponent::update(float deltaTime)
{
	model.shaderAttribute.setMat4("model", this->toModelMatrix());
}
