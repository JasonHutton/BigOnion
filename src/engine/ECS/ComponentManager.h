#pragma once

#include <unordered_map> 
#include "Component.fwd.h"

class ComponentManager
{
public:
	ComponentManager(std::string updateStrategy[], size_t n);
	void add(Component* component);
	bool remove(Component* component);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

private:
	ComponentManager();
	std::unordered_map<std::string, std::vector<Component*>*> componentPools;
	std::string* strategy;
	const size_t n;

};
