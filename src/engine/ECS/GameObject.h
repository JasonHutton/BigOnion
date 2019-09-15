#pragma once

#include <memory>
#include <string>
#include <vector>

class Component;

class GameObject
{
public:
	std::string id;
	GameObject(std::string id);
	void addComponent(std::unique_ptr<Component> component);
	void updateComponents(float deltaTime);
	void lateUpdateComponents(float deltaTime);

private:
	std::vector<std::unique_ptr<Component>> components;
	GameObject();

};
