#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include <iostream>

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body): rigidBody(_body)
{

}


void RigidBodyComponent::onAddToGameObject() {
	
	Vector3f pos = this->gameObject->transform.getPosition(); // will not be affect by the order or create components
	Vector3f rot = this->gameObject->transform.getRotation();


	this->gameObject->rigidBody = rigidBody;

	this->gameObject->transform.setPosition(pos);
	this->gameObject->transform.setRotation(rot);
}
