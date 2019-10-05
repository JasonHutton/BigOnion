#pragma once

#include "GameObject.fwd.h"

/*
	Component is an abstract class to be inherited from. The base class implements no functionality.
*/
class Component
{
public:
	GameObject* gameObject = nullptr;
	virtual ~Component() {};
	virtual void update(float deltaTime) {};
	virtual void lateUpdate(float deltaTime) {};
	virtual void fixedUpdate(float deltaTime) {};

	virtual void onAddToGameObject() {};
	
};
