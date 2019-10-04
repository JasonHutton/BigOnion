#include "RenderComponent.h"


void RenderComponent::lateUpdate(float deltaTime) {

	this->shaderAttribute->setMat4("model", gameObject->transform.getModelMatrix());

}
