#include "RenderComponent.h"
#include "../../engine/utils/Vector3.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/BOEngine.h"

const std::string RenderComponent::typeID = "Render";

RenderComponent::RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader)
	: model (modelPath, shader)
{
	engine->addRenderComponent(this);
}

void RenderComponent::update(float deltaTime)
{
	model.shaderAttribute.setMat4("model", gameObject->transform.toModelMatrix());
}
