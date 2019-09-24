#include "GameWorld.h"
#include "GameObject.h"

/*
	Initializes this Game World.
*/
GameWorld::GameWorld()
	: gameObjects(INIT_GAMEWORLD_SIZE)
{
}

/*
	Deconstructor.
*/
GameWorld::~GameWorld()
{
	gameObjects.clear();
}

/*
	Adds a Game Object to this Game World's component collection.
	Needs to be called with std::move() for this Game World to have ownership of the std::unique_ptr.
*/
void GameWorld::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObjects[gameObject->id] = std::move(gameObject);
}

void GameWorld::removeGameObject(std::string id)
{
	gameObjects.erase(id);
}

/*
	Calls the updateComponents() and lateUpdateComponents() functions of all Game Objects owned by this Game World.
*/
void GameWorld::updateGameObjects(float deltaTime)
{
	// first run the updateComponents method on each GameObject...
	for (auto& it : gameObjects)
	{
		GameObject* obj = it.second.get();
		obj->updateComponents(deltaTime);
	}

	// ...then run the lateUpdateComponents method on each GameObject
	for (auto& it : gameObjects)
	{
		GameObject* obj = it.second.get();
		obj->lateUpdateComponents(deltaTime);
	}
}
