#include "RenderComponent.h"
#include "../utils/Vector3.h"
#include "../ECS/GameObject.h"
#include "../BOEngine.h"

RenderComponent::RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader)
	: model (modelPath, shader)
{
	engine->addRenderComponent(this);
}

void RenderComponent::lateUpdate(float deltaTime)
{
	model.shaderAttribute.setMat4("model", gameObject->transform.toModelMatrix());
}
