#include "RenderComponent.h"
#include <iostream>

void RenderComponent::lateUpdate(float deltaTime)
{
	this->shaderAttribute->setMat4("model", gameObject->transform.toModelMatrix());
}