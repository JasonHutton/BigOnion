#pragma once

#include <unordered_map> 
#include "Component.fwd.h"

class ComponentManager
{
public:
	ComponentManager(std::string strategy[], size_t n);
	void add(Component* component);
	void remove(Component* component);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

private:
	ComponentManager();
	std::unordered_map<std::string, std::vector<Component*>*> componentPools;
	std::string* strategy;
	const size_t n;

};
