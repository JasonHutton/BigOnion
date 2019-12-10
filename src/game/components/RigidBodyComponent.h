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

	~RigidBodyComponent() override;

	void update(float deltaTime) override;
	void onAddToGameWorld() override;
	std::string componentTypeID() override { return "RigidBody"; }
	void applyForceRelativeToDirection(Vector3f force);
	void applyTorque(Vector3f torque);
	void setVelocityRelativeToDirection(Vector3f velocity);
	void setAngularVelocity(Vector3f velocity);
	Vector3f getVelocityRelativeToDirection();
	void printInfo();
	bool isHit(RigidBodyComponent* rbc);
	void setIdentity(int id) {
		identity = id;
	}
	int getIdentity() {
		return identity;
	}

	static RigidBodyComponent* createWithCube(float width, float height, float depth, float mass = 0, float bounciness = 0, int id = -1);
	static RigidBodyComponent* createWithPlane();
	static RigidBodyComponent* createWithCylinder(float width, float height, float depth, float mass = 0);
	static RigidBodyComponent* createWithMesh(Model* model, float bounciness = 0, int id = -1);

private:
	btRigidBody* rigidBody;
	int identity;
};
