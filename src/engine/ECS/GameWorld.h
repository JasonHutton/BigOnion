#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map> 
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

private:
	std::unordered_map<std::string, std::unique_ptr<GameObject>> gameObjects;

};
