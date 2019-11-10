#pragma once

#include "../src/engine/ECS/Component.h"
#include "RigidBodyComponent.h"

class CarControlComponent :
	public Component
{
public:

	static const std::string typeID;
	std::string componentTypeID() override { return typeID; }

	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime) override;
	void onAddToGameWorld() override;

	std::vector<GameObject*> tires;
private:
	RigidBodyComponent* rb;

	void rotateTiresAnima(float speed);
	void steerTiresAnima(float angle);
};
