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
	bool ignorePause = false;
	virtual ~Component() {};
	/*
		Used to apply behaviour every frame.
	*/
	virtual void update(float deltaTime) {};
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
	virtual std::string componentTypeID() = 0;
	/*
		Called when the GameWorld is paused.
	*/
	virtual void pauseExec() {};
	/*
		Called when the GameWorld is unpaused;
	*/
	virtual void unpauseExec() {};
};
