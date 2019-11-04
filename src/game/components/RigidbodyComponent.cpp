#include "RigidBodyComponent.h"
#include "../../engine/ECS/GameObject.h"
#include "../../engine/ECS/GameWorld.h"
#include <iostream>

const std::string RigidBodyComponent::typeID = "RigidBody";

RigidBodyComponent::RigidBodyComponent(btRigidBody* _body)
	: rigidBody(_body)
{
}


void RigidBodyComponent::fixedUpdate(float deltaTime)
{
	// position
	btTransform bTransform;

	if (rigidBody->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE || rigidBody->getMass() == 0) {
		bTransform = rigidBody->getWorldTransform();
	}
	else {
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

	gameObject->world->physicsWorld->addRigidBody(rigidBody);
}

void RigidBodyComponent::applyForwardForce()
{
	rigidBody->applyCentralForce(btVector3(10,0,0));
	cout << rigidBody->getWorldTransform().getOrigin().getX() << '\n';
}

void RigidBodyComponent::applyBackwardForce()
{
	rigidBody->applyCentralForce(btVector3(-10, 0, 0));
	cout << rigidBody->getWorldTransform().getOrigin().getX() << '\n';
}

/*
	Returns a RigidBodyComponent with an attached Cube collider.
*/
RigidBodyComponent* RigidBodyComponent::createWithCube(float width, float height, float depth, float mass)
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

	return new RigidBodyComponent(body);
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

RigidBodyComponent* RigidBodyComponent::createWithMesh(Model* model, float mass)
{
	btTransform t;	//position and rotation
	t.setIdentity();

	btTriangleMesh* triangleMesh = new btTriangleMesh();

	for (Mesh& mesh : model->getMeshes()) {
		for (int i = 0; i < mesh.indices.size() - 2; i += 3) {
			btVector3 point1 = btVector3(mesh.vertices[i].Position.x, mesh.vertices[i].Position.y, mesh.vertices[i].Position.z);
			btVector3 point2 = btVector3(mesh.vertices[i+1].Position.x, mesh.vertices[i + 1].Position.y, mesh.vertices[i + 1].Position.z);
			btVector3 point3 = btVector3(mesh.vertices[i+2].Position.x, mesh.vertices[i + 2].Position.y, mesh.vertices[i + 2].Position.z);
			triangleMesh->addTriangle(point1, point2, point3, true);
		}
	}

	btBvhTriangleMeshShape* bvhTriangleMeshShae = new btBvhTriangleMeshShape(triangleMesh, false);

	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		bvhTriangleMeshShae->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, bvhTriangleMeshShae, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself

	return new RigidBodyComponent(body);
}