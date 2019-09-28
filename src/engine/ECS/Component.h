#pragma once

#include "GameObject.fwd.h"

/*
	Component is an abstract class to be inherited from.
*/
class Component
{
public:
	GameObject* gameObject;
	virtual ~Component() {};
	virtual void update(float deltaTime) {};
	virtual void lateUpdate(float deltaTime) {};

};
