#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/ECS/GameWorld.h"

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body)
	: rigidBody(_body)
{
}


void RigidBodyComponent::fixedUpdate(float deltaTime)
{
	// position
	btTransform bTransform;
	rigidBody->getMotionState()->getWorldTransform(bTransform);
	gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	float z, y, x;
	bTransform.getRotation().getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);
}

void RigidBodyComponent::onAddToGameWorld()
{
	// position
	btTransform bTransform;
	rigidBody->getMotionState()->getWorldTransform(bTransform);
	gameObject->transform.position = Vector3f(bTransform.getOrigin().x(), bTransform.getOrigin().y(), bTransform.getOrigin().z());

	// rotation
	float z, y, x;
	bTransform.getRotation().getEulerZYX(z, y, x);
	gameObject->transform.rotation = Vector3f(x, y, z);

	//TODO: ABSOLUTELY FIX THIS
	/*
	Vector3f pos = gameObject->transform.position;
	trans.setOrigin(btVector3(gameObject->transform.position.x, pos.y, pos.z));
	rigidBody->setWorldTransform(trans);
	*/

	gameObject->world->physicsWorld->addRigidBody(rigidBody);
}

RigidBodyComponent* RigidBodyComponent::createWithCube(float width, float height, float depth, float x, float y, float z, float mass, float yaw, float pitch, float roll)
{
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btQuaternion quat;
	quat.setEuler(yaw, pitch, roll); //rotate it to yaw,pitch,roll angles
	t.setRotation(quat);
	btBoxShape* box = new btBoxShape(btVector3(width, height, depth)); // note cube's dimensions will be twice the input values as these refer to distance from the origin to the edge
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		box->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself

	return new RigidBodyComponent(body);
}

RigidBodyComponent* RigidBodyComponent::createWithPlane(float x, float y, float z)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);

	return new RigidBodyComponent(body);
}

RigidBodyComponent* RigidBodyComponent::createWithCylinder(float width, float height, float depth, float x, float y, float z, float mass, float yaw, float pitch, float roll)
{
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btQuaternion quat;
	quat.setEuler(yaw, pitch, roll);
	t.setRotation(quat);
	btCylinderShape* cylinder = new btCylinderShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		cylinder->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself

	return new RigidBodyComponent(body);
}
