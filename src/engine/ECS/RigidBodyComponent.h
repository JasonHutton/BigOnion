#pragma once
#include "Component.h"
#include "GameObject.h"

class RigidBodyComponent :
	public Component
{
public:
	RigidBodyComponent(btRigidBody*);

	void onAddToGameObject() override;

private:
	btRigidBody* rigidBody;
};

