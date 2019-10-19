#include "GameObject.h"
#include "Component.h"
#include "GameWorld.h"

/*
	Initializes this Game Object.
*/
GameObject::GameObject(std::string id)
	: id(id)
	, transform()
	, components()
	, world(nullptr)

{
}

/*
	Deconstructor.
*/
GameObject::~GameObject()
{
	for (Component* c : components)
	{
		world->componentManager->remove(c);
		delete c;
	}
}

/*
	Adds a component to this Game Object's component collection.
*/
void GameObject::addComponent(Component* component)
{
	component->gameObject = this;
	components.push_back(component);

	if (world != nullptr)
	{
		world->componentManager->add(component);
	}
}

/*
	Removes a component from this Game Object's component collection and deletes it.
*/
void GameObject::removeComponent(Component* component)
{
	for (auto iter = components.begin(); iter != components.end(); ++iter)
	{
		if (*iter == component)
		{
			components.erase(iter);
			delete component;
			return;
		}
	}
}

/*
	Removes a component from this Game Object's component collection and deletes it.
*/
void GameObject::removeComponent(int index)
{
	components.erase(components.begin() + index);
}

/*
	Sets the world reference for this GameObject and all components.
*/
void GameObject::addToGameWorld(GameWorld* world)
{
	this->world = world;
	for (Component* component : components)
	{
		component->onAddToGameWorld();
		this->world->componentManager->add(component);
	}
}

void* GameObject::operator new(size_t i)
{
	return _mm_malloc(i, 16);
}

void GameObject::operator delete(void* p)
{
	_mm_free(p);
}
