#include "CarControlComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/input/GameInput.h"

const std::string CarControlComponent::typeID = "CarControl";

CarControlComponent::CarControlComponent(float accelForce, float fullControlVel, float turnVel)
	: accelForce(accelForce)
	, fullControlVel(fullControlVel)
	, turnVel(turnVel)
	, rb(nullptr)
{
}

void CarControlComponent::update(float deltaTime)
{
	// grab inputs
	float forward = GameInput::getVerticalAxis();
	float turn = GameInput::getHorizontalAxis();

	// apply animations to tires
	rotateTiresAnima(forward);
	steerTiresAnima(turn);

	// apply acceleration force
	rb->applyForceRelativeToDirection(Vector3f(forward * accelForce, 0, 0));

	// get percentage of required speed for turning
	Vector3f vectorVel = rb->getVelocityRelativeToDirection();
	vectorVel = Vector3f(vectorVel.x, 0, vectorVel.z);
	float velocity = abs(vectorVel.length());
	float turnPercent = velocity / fullControlVel;
	if (turnPercent > 1)
	{
		turnPercent = 1;
	}
	else if (turnPercent < 0)
	{
		turnPercent = 0;
	}

	// reverse turning if car goes backward
	float direction = 1;
	if (forward != 0)
	{
		direction = -forward / abs(forward);
	}

	// apply turning
	rb->applyAngularVelocity(Vector3f(0, direction * turnPercent * turn * turnVel, 0));
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
