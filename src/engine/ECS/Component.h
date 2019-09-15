#pragma once

#include <memory>

class GameObject;

class Component
{
public:
	Component(GameObject* gameObject);
	virtual void update(float deltaTime) = 0;
	virtual void lateUpdate(float deltaTime) = 0;

private:
	Component();
	GameObject* gameObject;

};
