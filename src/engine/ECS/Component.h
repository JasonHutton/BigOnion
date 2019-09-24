#pragma once

#include <memory>
#include "GameObject.fwd.h"

class Component
{
public:
	Component(GameObject* gameObject);
	~Component();
	void update(float deltaTime);
	void lateUpdate(float deltaTime);

private:
	Component();
	GameObject* gameObject;

};
