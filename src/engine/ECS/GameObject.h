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
	GameObject* parent = nullptr;

	GameObject(std::string id);
	~GameObject();
	void addComponent(Component* component);
	bool removeComponent(Component* component);
	bool removeComponent(int index);
	template<typename T>
	T* getComponent();
	void addToGameWorld(GameWorld* world);
	void* operator new(size_t i);
	void operator delete(void* p);

private:
	std::vector<Component*> components;
	GameObject();

};

/*
	Returns the component of type T this GameObject holds, if it exists.
*/
template<typename T>
inline T* GameObject::getComponent()
{
	for (Component* component : components)
	{
		T* t = dynamic_cast<T*>(component);
		if (t != nullptr)
		{
			return t;
		}
	}
}
