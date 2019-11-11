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

	// find z velocity for sliding
	float velocityZ = rb->getVelocityRelativeToDirection().z;

	// apply acceleration and anti sliding force
	rb->applyForceRelativeToDirection(Vector3f(forward * accelForce, 0, velocityZ));
}

void CarControlComponent::fixedUpdate(float deltaTime)
{
	// grab inputs
	float turn = GameInput::getHorizontalAxis() * turnVel;

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
	rb->applyAngularVelocity(Vector3f(0, turnPercent * turn, 0));
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
