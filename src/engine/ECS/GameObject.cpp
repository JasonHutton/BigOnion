#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string id)
	: id(id)
{
}

void GameObject::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}

void GameObject::updateComponents(float deltaTime)
{
	for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {

		Component* component = (*it).get();
		component->update(deltaTime);
	}
}

void GameObject::lateUpdateComponents(float deltaTime)
{
	for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {

		Component* component = (*it).get();
		component->lateUpdate(deltaTime);
	}
}
