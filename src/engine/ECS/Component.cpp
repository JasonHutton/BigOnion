#include "Component.h"

/*
	Initializes this Component and store its parent Game Object.
*/
Component::Component(GameObject* gameObject)
	: gameObject(gameObject)
{
}

Component::~Component()
{
	// todo
}

