#include "Component.h"

/*
	Initializes this Component and store its parent Game Object.
*/
Component::Component(GameObject* gameObject)
	: gameObject(gameObject)
{
	// to be implemented by inheriting classes, default behaviour is nothing
}

/*
	Deconstructor.
*/
Component::~Component()
{
	// to be implemented by inheriting classes, default behaviour is nothing
}

/*
	Update method, to be implemented by inheriting classes.
*/
void Component::update(float deltaTime)
{
	// to be implemented by inheriting classes, default behaviour is nothing
}

/*
	:ate Update method, to be implemented by inheriting classes.
*/
void Component::lateUpdate(float deltaTime)
{
	// to be implemented by inheriting classes, default behaviour is nothing
}
