#include "GameObject.h"
#include "Component.h"

/*
	Initializes this Game Object with an id.
*/
GameObject::GameObject(std::string id)
	: id(id)
{
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
	for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {

		Component* component = (*it).get();
		component->update(deltaTime);
	}
}

/*
	Calls the lateUpdate() function of all components owned by this Game Object.
*/
void GameObject::lateUpdateComponents(float deltaTime)
{
	for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {

		Component* component = (*it).get();
		component->lateUpdate(deltaTime);
	}
}
