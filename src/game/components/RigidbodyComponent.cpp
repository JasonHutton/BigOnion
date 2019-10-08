#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include <iostream>

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body)
	: rigidBody(_body)
{
}


void RigidBodyComponent::fixedUpdate(float deltaTime)
{
	// position
	btTransform bTransform = rigidBody->getWorldTransform();
	gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	btMatrix3x3 rotMatrix = btMatrix3x3(bTransform.getRotation());
	float z, y, x;
	rotMatrix.getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);
}

void RigidBodyComponent::onAddToGameObject()
{
	btTransform trans = rigidBody->getWorldTransform();
	gameObject->transform.position = Vector3f(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
	//TODO: ABSOLUTELY FIX THIS
	/*
	Vector3f pos = gameObject->transform.position;
	trans.setOrigin(btVector3(gameObject->transform.position.x, pos.y, pos.z));
	rigidBody->setWorldTransform(trans);
	*/
}
