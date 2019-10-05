#pragma once

#include <string>
#include <vector>
#include <btBulletDynamicsCommon.h>

#include "Component.h"
#include "TransformComponent.h"

class GameObject
{
public:
	std::string id;
	TransformComponent transform;
	btRigidBody* rigidBody = nullptr;

	GameObject(std::string id);
	~GameObject();
	void addComponent(Component* component);
	void updateComponents(float deltaTime);
	void lateUpdateComponents(float deltaTime);
	void fixedUpdateComponents(float deltaTime);

private:
	std::vector<Component*> components;
	GameObject();

};
