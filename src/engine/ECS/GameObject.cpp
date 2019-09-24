#include "GameObject.h"
#include "Component.h"

/*
	Initializes this Game Object.
*/
GameObject::GameObject(std::string id)
	: id(id)
	, components()
{
}

/*
	Deconstructor.
*/
GameObject::~GameObject()
{
	components.clear();
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
