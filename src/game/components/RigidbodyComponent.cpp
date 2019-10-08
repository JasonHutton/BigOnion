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

/*
void Transform::setPosition(Vector3f pos) {

	position = pos;

	if (hasRigidBody()) {
		btRigidBody* _body = gameObject->rigidBody;

		btTransform trans = _body->getWorldTransform();
		trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
		_body->setWorldTransform(trans);
	}

}

void Transform::setRotation(Vector3f rt) {

	if (hasRigidBody()) {

		btTransform trans = gameObject->rigidBody->getWorldTransform();
		btQuaternion rot = trans.getRotation();

		Vector3f currentRt_ = this->getRotation();

		//		if (gameObject->id == "Box")
		//			std::cout << hasRigidBody() << " - "<< rt.z << std::endl;

		btQuaternion quat;
		quat.setEulerZYX(rt.z, rt.y, rt.x); // quat.setEulerZYX, yaw, pitch, roll
		trans.setRotation(quat);

		gameObject->rigidBody->setWorldTransform(trans);
	}

	rotation = rt;
}
*/
