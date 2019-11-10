#pragma once
#include "../../engine/ECS/Component.h"
#include <btBulletDynamicsCommon.h>
#include <glm\gtc\type_ptr.hpp>
#include "../../engine/graphic/model.h"
#include "../../engine/utils/vector3.h"

class RigidBodyComponent :
	public Component
{
public:
	static const std::string typeID;
	RigidBodyComponent(btRigidBody*);

	void update(float deltaTime) override;
	void onAddToGameWorld() override;
	std::string componentTypeID() override { return "RigidBody"; }
	void applyForceRelativeToDirection(Vector3f force);
	void applyTorque(Vector3f torque);
	void applyAngularVelocity(Vector3f velocity);
	Vector3f getVelocityRelativeToDirection();
	void printInfo();

	static RigidBodyComponent* createWithCube(float width, float height, float depth, float mass);
	static RigidBodyComponent* createWithPlane();
	static RigidBodyComponent* createWithCylinder(float width, float height, float depth, float mass);
	static RigidBodyComponent* createWithMesh(Model* model, float mass);

private:
	btRigidBody* rigidBody;
};
