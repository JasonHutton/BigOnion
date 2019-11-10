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

	rotateTiresAnima(1); 
	steerTiresAnima(-inputY);
}

void CarControlComponent::rotateTiresAnima(float speed)
{
	Transform carTransform = gameObject->transform;
	for (int i = 0; i < 4; i++) {
		this->tires[i]->transform.rotation += Vector3f(0, 0, -speed);
	}
}

void CarControlComponent::steerTiresAnima(float angle)
{
	float y = this->tires[0]->transform.rotation.y;
	float maxAngle = angle > 0 ? 0.9 : -0.9; // about 45 degree
	float delta = abs(angle) < FLT_EPSILON ? -y / 20 : (maxAngle - y) / 30; //  

	this->tires[0]->transform.rotation.y += delta;
	this->tires[1]->transform.rotation.y += delta;
}

void CarControlComponent::onAddToGameWorld()
{
	rb = gameObject->getComponent<RigidBodyComponent>();
}
