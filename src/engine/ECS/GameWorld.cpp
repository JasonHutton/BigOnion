#include "GameWorld.h"
#include "GameObject.h"
#include <iostream>

/*
	Initializes this Game World.
*/
GameWorld::GameWorld()
	: gameObjects()
{
}

/*
	Deconstructor.
*/
GameWorld::~GameWorld()
{
	for (auto& pair : gameObjects)
	{
		delete pair.second;
	}
}

/*
	Adds a Game Object to this Game World's component collection.
*/
void GameWorld::addGameObject(GameObject* gameObject)
{
	gameObjects.emplace(std::pair<std::string, GameObject*>(gameObject->id, gameObject));
}

void GameWorld::removeGameObject(std::string id)
{
	delete gameObjects[id];
	gameObjects.erase(id);
}

/*
	Calls the updateComponents() and lateUpdateComponents() functions of all Game Objects owned by this Game World.
*/
void GameWorld::updateGameObjects(float deltaTime)
{
	// first run the updateComponents method on each GameObject...
	for (auto& pair : gameObjects)
	{
		pair.second->updateComponents(deltaTime);
	}

	// ...then run the lateUpdateComponents method on each GameObject
	for (auto& pair : gameObjects)
	{
		pair.second->lateUpdateComponents(deltaTime);
	}
}
