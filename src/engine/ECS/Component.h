#pragma once

#include <memory>
#include "GameObject.fwd.h"

class Component
{
public:
	Component(GameObject* gameObject);
	~Component();
	virtual void update(float deltaTime) = 0;
	virtual void lateUpdate(float deltaTime) = 0;

private:
	Component();
	GameObject* gameObject;

};
