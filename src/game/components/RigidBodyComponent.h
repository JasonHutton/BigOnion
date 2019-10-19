#pragma once
#include "../../engine/ECS/Component.h"
#include <btBulletDynamicsCommon.h>
#include <glm\gtc\type_ptr.hpp>

class RigidBodyComponent :
	public Component
{
public:
	static const std::string typeID;
	RigidBodyComponent(btRigidBody*);

	void fixedUpdate(float deltaTime) override;
	void onAddToGameWorld() override;
	std::string componentTypeID() override { return "RigidBody"; }

	static RigidBodyComponent* createWithCube(float width, float height, float depth, float mass);
	static RigidBodyComponent* createWithPlane();
	static RigidBodyComponent* createWithCylinder(float width, float height, float depth, float mass);

private:
	btRigidBody* rigidBody;
};
