#include "GameObject.h"
#include "Component.h"

/*
	Initializes this Game Object.
*/
GameObject::GameObject(std::string id)
	: id(id)
	, transform()
	, components()
	, world(nullptr)

{
	// components.push_back(&transform); // this line will cause program terminate....why? dead lopp?
}

/*
	Deconstructor.
*/
GameObject::~GameObject()
{
	for (Component* c : components)
	{
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
}

/*
	Calls the update() function of all components owned by this Game Object.
*/
void GameObject::updateComponents(float deltaTime)
{
	for (Component* component : components)
	{
		component->update(deltaTime);
	}
}

/*
	Calls the lateUpdate() function of all components owned by this Game Object.
*/
void GameObject::lateUpdateComponents(float deltaTime)
{
	for (Component* component : components)
	{
		component->lateUpdate(deltaTime);
	}
}

/*
	Calls the fixedUpdate() function of all components owned by this Game Object.
*/
void GameObject::fixedUpdateComponents(float deltaTime)
{
	for (Component* component : components)
	{
		component->fixedUpdate(deltaTime);
	}
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
	}
}
