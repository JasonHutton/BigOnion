#include "ComponentManager.h"
#include "Component.h"

ComponentManager::ComponentManager(std::string updateStrategy[], size_t n)
	: n(n)
{
	strategy = new std::string[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		strategy[i] = updateStrategy[i];
	}
}

/*
	Add a component to be updated.
*/
void ComponentManager::add(Component* component)
{
	std::string id = component->componentTypeID();
	componentPools[id].push_back(component);
}

/*
	Remove a component from the update list.
*/
bool ComponentManager::remove(Component* component)
{
	std::string id = component->componentTypeID();
	std::vector<Component*>* pool = &componentPools[id];

	for (auto iter = pool->begin(); iter != pool->end(); ++iter)
	{
		if (*iter == component)
		{
			pool->erase(iter);
			return true;
		}
	}

	return false;
}

/*
	Calls the update function of all components in the order of the strategy order.
*/
void ComponentManager::update(float deltaTime)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];
		for (Component* component : componentPools[id])
		{
			component->update(deltaTime);
		}
	}
}

/*
	Calls the fixed update function of all components in the order of the strategy order.
*/
void ComponentManager::fixedUpdate(float deltaTime)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];
		for (Component* component : componentPools[id])
		{
			component->fixedUpdate(deltaTime);
		}
	}
}
