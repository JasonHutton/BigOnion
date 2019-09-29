#pragma once

#include <string>
#include <unordered_map> 
#include "GameObject.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void addGameObject(GameObject* gameObject);
	void removeGameObject(std::string id);
	void updateGameObjects(float deltaTime);
	void fixedUpdateGameObjects(float deltaTime);

private:
	std::unordered_map<std::string, GameObject*> gameObjects;

};
