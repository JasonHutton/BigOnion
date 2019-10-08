#include "RenderComponent.h"
#include "../../engine/utils/Vector3.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/BOEngine.h"

RenderComponent::RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader)
	: model (modelPath, shader)
{
	engine->addRenderComponent(this);
}

void RenderComponent::lateUpdate(float deltaTime)
{
	model.shaderAttribute.setMat4("model", gameObject->transform.toModelMatrix());
}
