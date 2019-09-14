#pragma once

#include <memory>

class GameObject;

class Component
{
public:
	Component(std::weak_ptr<GameObject> gameObject);
	void update(float deltaTime);
	void lateUpdate(float deltaTime);

private:
	Component();
	std::weak_ptr<GameObject> gameObject;

};
