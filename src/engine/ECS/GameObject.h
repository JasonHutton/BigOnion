#pragma once

#include <string>
#include <vector>
#include <btBulletDynamicsCommon.h>

#include "Component.h"
#include "Transform.h"

class GameObject
{
public:
	std::string id;
	Transform transform;

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
