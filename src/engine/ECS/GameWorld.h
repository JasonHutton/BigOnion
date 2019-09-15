#pragma once

#include <memory>
#include <string>
#include <vector>
#include "GameObject.fwd.h"

constexpr int INIT_GAMEWORLD_SIZE = 5;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void addGameObject(std::unique_ptr<GameObject> gameObject);
	void removeGameObject(std::string id);
	void updateGameObjects(float deltaTime);
	void teardownWorld();

private:
	std::vector<std::unique_ptr<GameObject>> gameObjects; // TODO: consider using a hash table to give each game object a unique id

};
