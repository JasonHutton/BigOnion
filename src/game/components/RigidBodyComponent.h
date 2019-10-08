#pragma once
#include "../../engine/ECS/Component.h"
#include <btBulletDynamicsCommon.h>

class RigidBodyComponent :
	public Component
{
public:
	RigidBodyComponent(btRigidBody*);

	void onAddToGameObject() override;

private:
	btRigidBody* rigidBody;
};
