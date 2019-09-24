#include <type_traits>
#include "GameObject.h"
#include "Component.h"

/*
	Initializes this Game Object with an id.
*/
GameObject::GameObject(std::string id)
	: id(id)
	,components(INIT_COMPONENTS_SIZE)
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
	Needs to be called with std::move() for this Game Object to have ownership of the std::unique_ptr.
*/
void GameObject::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}

/*
	Calls the update() function of all components owned by this Game Object.
*/
void GameObject::updateComponents(float deltaTime)
{
	for (auto& it : components)
	{
		Component* component = it.get();
		component->update(deltaTime);
	}
}

/*
	Calls the lateUpdate() function of all components owned by this Game Object.
*/
void GameObject::lateUpdateComponents(float deltaTime)
{
	for (auto& it : components)
	{
		Component* component = it.get();
		component->lateUpdate(deltaTime);
	}
}
