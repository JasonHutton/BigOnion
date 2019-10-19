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
	void addToGameWorld(GameWorld* world);

private:
	std::vector<Component*> components;
	GameObject();

};
