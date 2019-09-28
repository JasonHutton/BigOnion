#pragma once

#include <string>
#include <vector>
#include "Component.h"

class GameObject
{
public:
	std::string id;
	GameObject(std::string id);
	~GameObject();
	void addComponent(Component* component);
	void updateComponents(float deltaTime);
	void lateUpdateComponents(float deltaTime);

private:
	std::vector<Component*> components;
	GameObject();

};
