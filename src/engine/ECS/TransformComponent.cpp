#include "TransformComponent.h"

#include "GameObject.h"
#include <iostream>

TransformComponent::TransformComponent() : position(), rotation(), scale()
{

}

bool TransformComponent::hasRigidBody()
{
	if(this->gameObject != nullptr){
		return this->gameObject->rigidBody != nullptr;
	}
	return false;
}

glm::mat4 TransformComponent::getModelMatrix() {

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	if (hasRigidBody()) {
		btTransform transform= gameObject->rigidBody->getWorldTransform();	//get the transform
		transform.getOpenGLMatrix(glm::value_ptr(modelMatrix));
	}
	else {
		modelMatrix = glm::translate(modelMatrix, getPosition().getGlmVec3());

		Vector3f* rotation_ = &getRotation();
		modelMatrix = glm::rotate(modelMatrix, rotation_->x, glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, rotation_->y, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, rotation_->z, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	return glm::scale(modelMatrix, getScale().getGlmVec3());
}

Vector3f TransformComponent::getPosition()
{
	if (hasRigidBody()) {
		btTransform trans = gameObject->rigidBody->getWorldTransform();
		position = Vector3f(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
	}

	return position;
}


void TransformComponent::setPosition(Vector3f pos) {
	
	position = pos;

	if (hasRigidBody()) {
		btRigidBody* _body = gameObject->rigidBody;

		btTransform trans = _body->getWorldTransform();
		trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
		_body->setWorldTransform(trans);
	}

}

Vector3f TransformComponent::getRotation() {
	if (hasRigidBody()) {

		btMatrix3x3 rotMatrix = btMatrix3x3(gameObject->rigidBody->getWorldTransform().getRotation());
		float z, y, x;
		rotMatrix.getEulerZYX(z, y, x);
		rotation = Vector3f(x, y, z);
	}

	return rotation;
}

void TransformComponent::setRotation(Vector3f rt) {

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

Vector3f TransformComponent::getScale() {
	return scale;
}

void TransformComponent::setScale(Vector3f sc) {
	return scale = sc;
}

void TransformComponent::setScale(float sc) {
	return scale = Vector3f(sc, sc, sc);
}