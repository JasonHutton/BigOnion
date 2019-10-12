#pragma once
#include "../../engine/ECS/Component.h"
#include <btBulletDynamicsCommon.h>

class RigidBodyComponent :
	public Component
{
public:
	RigidBodyComponent(btRigidBody*);

	void fixedUpdate(float deltaTime) override;
	void onAddToGameWorld() override;

	static RigidBodyComponent* createWithCube(float width, float height, float depth, float x, float y, float z, float mass, float yaw, float pitch, float roll);
	static RigidBodyComponent* createWithPlane(float x, float y, float z);
	static RigidBodyComponent* createWithCylinder(float width, float height, float depth, float x, float y, float z, float mass, float yaw, float pitch, float roll);

private:
	btRigidBody* rigidBody;
};
