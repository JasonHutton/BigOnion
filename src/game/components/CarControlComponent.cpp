#include "CarControlComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/input/GameInput.h"

const std::string CarControlComponent::typeID = "CarControl";

void CarControlComponent::update(float deltaTime)
{
	rotateTiresAnima(GameInput::getVerticalAxis());
	steerTiresAnima(GameInput::getHorizontalAxis());
}

void CarControlComponent::fixedUpdate(float deltaTime)
{
	// magic numbers ahoy!
	float fullControlVel = 15;
	float accelForce = 10;
	float turnVel = 2.5;

	// grab inputs
	float inputY = GameInput::getVerticalAxis();
	float inputX = GameInput::getHorizontalAxis();

	// apply acceleration force
	rb->applyForceRelativeToDirection(Vector3f(inputY * accelForce, 0, 0));

	// get percentage of required speed for turning
	Vector3f velocityVec = rb->getVelocityRelativeToDirection();
	velocityVec = Vector3f(velocityVec.x, 0, velocityVec.z);
	float velocity = abs(velocityVec.length());
	float turnPercent = velocity / fullControlVel;
	if (turnPercent > 1)
	{
		turnPercent = 1;
	}
	else if (turnPercent < 0)
	{
		turnPercent = 0;
	}

	// apply turning
	rb->applyAngularVelocity(Vector3f(0, turnPercent * inputX * turnVel, 0));
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
