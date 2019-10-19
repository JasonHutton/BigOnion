#include "ComponentManager.h"
#include "Component.h"

ComponentManager::ComponentManager(std::string strategy[], size_t n)
	: n(n)
{
	this->strategy = new std::string[n];

	for (unsigned int i = 0; i < n; ++i)
	{
		this->strategy[i] = strategy[i];
	}
}

/*
	Add a component to be updated.
*/
void ComponentManager::add(Component* component)
{
	std::string id = component->componentTypeID();

	// if the vector has not been initialized, initialize it
	if (componentPools.find(id) == componentPools.end())
	{
		componentPools[id] = new std::vector<Component*>();
	}

	std::vector<Component*>* pool = componentPools[id];
	pool->push_back(component);
}

/*
	Remove a component from the update list.
*/
void ComponentManager::remove(Component* component)
{
	std::string id = component->componentTypeID();
	std::vector<Component*>* pool = componentPools[id];

	for (auto iter = pool->begin(); iter != pool->end(); ++iter)
	{
		if (*iter == component)
		{
			pool->erase(iter);
			return;
		}
	}
}

/*
	Calls the update function of all components in the order of the strategy order.
*/
void ComponentManager::update(float deltaTime)
{
	for (unsigned int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];
		std::vector<Component*>* pool = componentPools[id];
		for (Component* component : *pool)
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
		std::vector<Component*>* pool = componentPools[id];
		for (Component* component : *pool)
		{
			component->fixedUpdate(deltaTime);
		}
	}
}
