#include "ComponentManager.h"
#include "Component.h"

void ComponentManager::add(Component* component)
{
	std::string id = component->getComponentTypeIdentifier();
	std::vector<Component*> pool = componentPools[id];
	pool.push_back(component);
}

void ComponentManager::remove(Component* component)
{
	std::string id = component->getComponentTypeIdentifier();
	std::vector<Component*> pool = componentPools[id];

	for (auto iter = pool.begin(); iter != pool.end(); ++iter)
	{
		if (*iter == component)
		{
			pool.erase(iter);
			return;
		}
	}
}

template <unsigned int N>
void ComponentManager::update(float deltaTime, std::string const (&strategy)[N])
{
	for (int i = 0; i < N; ++i)
	{
		std::string id = strategy[i];
		std::vector<Component*> pool = componentPools[id];
		for (Component* component : pool)
		{
			component->update();
		}
	}
}

template <unsigned int N>
void ComponentManager::fixedUpdate(float deltaTime, std::string const (&strategy)[N])
{
	for (int i = 0; i < N; ++i)
	{
		std::string id = strategy[i];
		std::vector<Component*> pool = componentPools[id];
		for (Component* component : pool)
		{
			component->fixedUpdate();
		}
	}
}
