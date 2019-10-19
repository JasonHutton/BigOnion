#pragma once

#include <string>
#include "GameObject.fwd.h"

/*
	Component is an abstract class to be inherited from. The base class implements no functionality.
*/
class Component
{
public:
	GameObject* gameObject = nullptr;
	virtual ~Component() {};
	/*
		Used to apply behaviour every frame.
	*/
	virtual void update(float deltaTime) {};
	/*
		Used to apply behaviour every frame, after update.
	*/
	virtual void lateUpdate(float deltaTime) {};
	/*
		Used to apply behaviour on a fixed timestep.
	*/
	virtual void fixedUpdate(float deltaTime) {};
	/*
		Used to initialize a component once it is added to the GameWorld.
	*/
	virtual void onAddToGameWorld() {};
	/*
		Pure virtual component type id function, this MUST be implemented in subclasses.
	*/
	virtual std::string getComponentTypeIdentifier() = 0;
};
