#include "ComponentManager.h"
#include "Component.h"

ComponentManager::ComponentManager(std::string strategy[], size_t n)
	: n(n)
{
	this->strategy = new std::string[n];

	for (int i = 0; i < n; ++i)
	{
		this->strategy[i] = strategy[i];
	}
}

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

void ComponentManager::update(float deltaTime)
{
	for (int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];
		std::vector<Component*>* pool = componentPools[id];
		for (Component* component : *pool)
		{
			component->update(deltaTime);
		}
	}
}

void ComponentManager::fixedUpdate(float deltaTime)
{
	for (int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];
		std::vector<Component*>* pool = componentPools[id];
		for (Component* component : *pool)
		{
			component->fixedUpdate(deltaTime);
		}
	}
}
