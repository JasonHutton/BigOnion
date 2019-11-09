#include "CarControlComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/input/GameInput.h"

const std::string CarControlComponent::typeID = "CarControl";

void CarControlComponent::update(float deltaTime)
{
	float inputX = GameInput::getVerticalAxis() * 10;
	float inputY = GameInput::getHorizontalAxis() * 10;
	rb->applyForce(Vector3f(inputX, 0, 0));
	rb->applyTorque(Vector3f(0, inputY, 0));
}

void CarControlComponent::onAddToGameWorld()
{
	rb = gameObject->getComponent<RigidBodyComponent>();
}
