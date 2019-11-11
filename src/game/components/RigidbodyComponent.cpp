#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/ECS/GameWorld.h"
#include <iostream>

const std::string RigidBodyComponent::typeID = "RigidBody";

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body)
	: rigidBody(_body), identity(-1)
{
}


void RigidBodyComponent::update(float deltaTime)
{
	// position
	btTransform bTransform;

	if (rigidBody->getMass() == 0) { // if object is static
		bTransform = rigidBody->getWorldTransform();
	}
	else { // if it is dynamic
		rigidBody->getMotionState()->getWorldTransform(bTransform);
	}

	gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	float z, y, x;
	bTransform.getRotation().getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);
}

void RigidBodyComponent::onAddToGameWorld()
{
	btTransform bTransform;
	bTransform.setOrigin(btVector3(gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z));	//put it to x,y,z coordinates

	btQuaternion quat;
	quat.setEuler(gameObject->transform.rotation.z, gameObject->transform.rotation.y, gameObject->transform.rotation.x); //rotate it to yaw, pitch, roll (z,y,x) angles
	bTransform.setRotation(quat);

	rigidBody->setWorldTransform(bTransform);
	rigidBody->setUserPointer(this);
	gameObject->world->physicsWorld->addRigidBody(rigidBody);
}

void RigidBodyComponent::applyForceRelativeToDirection(Vector3f force)
{
	//for moving forward and back, code taken from https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=2366
	btVector3 relativeForce = btVector3(force.x, force.y, force.z);
	btMatrix3x3& boxRot = rigidBody->getWorldTransform().getBasis();
	btVector3 correctedForce = boxRot * relativeForce;
	rigidBody->applyCentralForce(correctedForce);
}

// NOT USED, can we get rid of this?
void RigidBodyComponent::applyTorque(Vector3f torque) 
{
	rigidBody->applyTorque(btVector3(torque.x, torque.y, torque.z));
}

void RigidBodyComponent::applyAngularVelocity(Vector3f velocity)
{
	rigidBody->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}

float RigidBodyComponent::getSlideVelocity()
{
	btMatrix3x3& boxRot = rigidBody->getWorldTransform().getBasis();
	btVector3 relativeVelocity = boxRot * btVector3(rigidBody->getLinearVelocity().x(), rigidBody->getLinearVelocity().y(), -rigidBody->getLinearVelocity().z());
	return relativeVelocity.z();
}

Vector3f RigidBodyComponent::getVelocityRelativeToDirection()
{
	btMatrix3x3& boxRot = rigidBody->getWorldTransform().getBasis();
	btVector3 relativeVelocity = boxRot * rigidBody->getLinearVelocity();
	return Vector3f(relativeVelocity.x(), relativeVelocity.y(), relativeVelocity.z());
}

void RigidBodyComponent::printInfo()
{
	std::cout << "total: " << rigidBody->getTotalForce().length() << std::endl;
}

void RigidBodyComponent::isHit(RigidBodyComponent* rbc) {
	if (identity == 0 && rbc->identity == 1) { //check if this is the care and we are colliding with the wall
		cout << "collision" << endl;
	}
	/*else {
		cout << "no collision" << endl;
	}*/
}

/*
	Returns a RigidBodyComponent with an attached Cube collider.
*/
RigidBodyComponent* RigidBodyComponent::createWithCube(float width, float height, float depth, float mass, float bounciness, int id)
{
	btTransform t;	//position and rotation
	t.setIdentity();

	btBoxShape* box = new btBoxShape(btVector3(width, height, depth)); // note cube's dimensions will be twice the input values as these refer to distance from the origin to the edge
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		box->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself

	body->setActivationState(DISABLE_DEACTIVATION);
	body->setRestitution(bounciness);
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

	RigidBodyComponent* rbc = new RigidBodyComponent(body);
	rbc->setIdentity(id);
	return rbc;
}

/*
	Returns a RigidBodyComponent with an attached Plane collider.
*/
RigidBodyComponent* RigidBodyComponent::createWithPlane()
{
	btTransform t;
	t.setIdentity();

	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);

	return new RigidBodyComponent(body);
}

/*
	Returns a RigidBodyComponent with an attached Cylinder collider.
*/
RigidBodyComponent* RigidBodyComponent::createWithCylinder(float width, float height, float depth, float mass)
{
	btTransform t;	//position and rotation
	t.setIdentity();
	btCylinderShape* cylinder = new btCylinderShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		cylinder->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself

	return new RigidBodyComponent(body);
}

RigidBodyComponent* RigidBodyComponent::createWithMesh(Model* model, float bounciness, int id)
{
	btTransform t;	//position and rotation
	t.setIdentity();

	btTriangleMesh* triangleMesh = new btTriangleMesh();

	for (Mesh& mesh : model->getMeshes()) {
		for (int i = 0; i < mesh.indices.size() - 2; i += 3) {
			btVector3 point1 = btVector3(mesh.vertices[i].Position.x, mesh.vertices[i].Position.y, mesh.vertices[i].Position.z);
			btVector3 point2 = btVector3(mesh.vertices[i + 1].Position.x, mesh.vertices[i + 1].Position.y, mesh.vertices[i + 1].Position.z);
			btVector3 point3 = btVector3(mesh.vertices[i + 2].Position.x, mesh.vertices[i + 2].Position.y, mesh.vertices[i + 2].Position.z);
			triangleMesh->addTriangle(point1, point2, point3, true);
		}
	}

	btBvhTriangleMeshShape* bvhTriangleMeshShape = new btBvhTriangleMeshShape(triangleMesh, false);

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, bvhTriangleMeshShape);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself
	body->setRestitution(1.0);

	RigidBodyComponent* rbc = new RigidBodyComponent(body);
	rbc->setIdentity(id);

	return rbc;
}
