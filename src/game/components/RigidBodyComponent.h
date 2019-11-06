#pragma once
#include "../../engine/ECS/Component.h"
#include <btBulletDynamicsCommon.h>
#include <glm\gtc\type_ptr.hpp>
#include "../../engine/graphic/model.h"

class RigidBodyComponent :
	public Component
{
public:
	static const std::string typeID;
	RigidBodyComponent(btRigidBody*);

	void update(float deltaTime) override;
	void onAddToGameWorld() override;
	std::string componentTypeID() override { return "RigidBody"; }
	void applyForwardForce();
	void applyBackwardForce();

	static RigidBodyComponent* createWithCube(float width, float height, float depth, float mass);
	static RigidBodyComponent* createWithPlane();
	static RigidBodyComponent* createWithCylinder(float width, float height, float depth, float mass);
	static RigidBodyComponent* createWithMesh(Model* model, float mass);

private:
	btRigidBody* rigidBody;
};
