#include "CarControlComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/input/GameInput.h"

const std::string CarControlComponent::typeID = "CarControl";

void CarControlComponent::update(float deltaTime)
{
	rb->applyForce(GameInput::getAxes() * 10);
	rb->applyTorque(GameInput::getAxes() * 10);
}

void CarControlComponent::onAddToGameWorld()
{
	rb = gameObject->getComponent<RigidBodyComponent>();
}
