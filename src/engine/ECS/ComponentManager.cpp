#include "ComponentManager.h"
#include "Component.h"

ComponentManager::ComponentManager(std::string updateStrategy[], size_t n)
	: n(n)
	, isPaused(false)
	, threadPool(10)
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
	auto futureBuffer = std::vector<std::future<void>>();

	for (unsigned int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];

		std::vector<Component*>* componentPool = &componentPools[id];
		int count = componentPool->size();

		for (Component* component : *componentPool)
		{
			if (!isPaused || component->ignorePause)
			{
				auto future = threadPool.enqueue([](Component* component, int deltaTime) { component->update(deltaTime); }, component, deltaTime);
				futureBuffer.push_back(std::move(future));
			}
		}

		for (auto& future : futureBuffer)
		{
			future.wait();
		}

		futureBuffer.clear();
	}
}

/*
	Calls the fixed update function of all components in the order of the strategy order.
*/
void ComponentManager::fixedUpdate(float deltaTime)
{
	auto futureBuffer = std::vector<std::future<void>>();

	for (unsigned int i = 0; i < n; ++i)
	{
		std::string id = strategy[i];

		std::vector<Component*>* componentPool = &componentPools[id];
		int count = componentPool->size();

		for (Component* component : *componentPool)
		{
			if (!isPaused || component->ignorePause)
			{
				auto future = threadPool.enqueue([](Component* component, int deltaTime) { component->fixedUpdate(deltaTime); }, component, deltaTime);
				futureBuffer.push_back(std::move(future));
			}
		}

		for (auto& future : futureBuffer)
		{
			future.wait();
		}

		futureBuffer.clear();
	}
}

/*
	Stops the execution of updates.
*/
void ComponentManager::pause()
{
	isPaused = true;
}

/*
	Continues the execution of updates.
*/
void ComponentManager::unpause()
{
	isPaused = false;
}
