#include "CarControlComponent.h"
#include "../../engine/ECS/GameObject.h"

const std::string CarControlComponent::typeID = "CarControl";

void CarControlComponent::update(float deltaTime)
{

}

void CarControlComponent::onAddToGameWorld()
{
	rb = gameObject->getComponent<RigidBodyComponent>();
}
