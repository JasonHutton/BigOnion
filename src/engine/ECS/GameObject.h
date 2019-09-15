#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Component.fwd.h"

constexpr int INIT_COMPONENTS_SIZE = 5;

class GameObject
{
public:
	std::string id;
	GameObject(std::string id);
	~GameObject();
	void addComponent(std::unique_ptr<Component> component);
	void updateComponents(float deltaTime);
	void lateUpdateComponents(float deltaTime);

private:
	std::vector<std::unique_ptr<Component>> components;
	GameObject();

};
