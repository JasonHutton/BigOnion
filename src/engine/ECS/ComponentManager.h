#pragma once

#include <unordered_map> 
#include "Component.fwd.h"

class ComponentManager
{
public:
	void add(Component* component);
	void remove(Component* component);
	template <unsigned int N>
	void update(float deltaTime, std::string const (&strategy)[N]);
	template <unsigned int N>
	void fixedUpdate(float deltaTime, std::string const (&strategy)[N]);

private:
	std::unordered_map<std::string, std::vector<Component*>> componentPools;

};
