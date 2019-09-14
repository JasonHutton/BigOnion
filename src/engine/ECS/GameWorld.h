#pragma once

#include <memory>
#include <string>
#include <vector>

class GameObject;

class GameWorld
{
public:
	void addGameObject(std::unique_ptr<GameObject> gameObject);
	void removeGameObject(std::string id);
	void updateGameObjects(float deltaTime);
	void teardownWorld();

private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

};
