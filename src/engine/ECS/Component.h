#pragma once

#include "GameObject.fwd.h"

class Component
{
public:
	GameObject* gameObject;
	virtual void update(float deltaTime);
	virtual void lateUpdate(float deltaTime);

};
