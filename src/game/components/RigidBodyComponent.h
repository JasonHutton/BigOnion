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

private:
	btRigidBody* rigidBody;
};
