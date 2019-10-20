#pragma once

#include <string>
#include <vector>
#include <btBulletDynamicsCommon.h>

#include "Component.h"
#include "Transform.h"
#include "GameWorld.fwd.h"

class GameObject
{
public:
	std::string id;
	Transform transform;
	GameWorld* world;

	GameObject(std::string id);
	~GameObject();
	void addComponent(Component* component);
	bool removeComponent(Component* component);
	bool removeComponent(int index);
	void addToGameWorld(GameWorld* world);
	void* operator new(size_t i);
	void operator delete(void* p);

private:
	std::vector<Component*> components;
	GameObject();

};
