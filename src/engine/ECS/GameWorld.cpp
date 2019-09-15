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
	Adds a Game Object to this Game World's component collection.
	Needs to be called with std::move() for this Game World to have ownership of the std::unique_ptr.
*/
void GameWorld::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObjects.push_back(std::move(gameObject));
}

void GameWorld::removeGameObject(std::string id)
{
	// todo
}

/*
	Calls the updateComponents() and lateUpdateComponents() functions of all Game Objects owned by this Game World.
*/
void GameWorld::updateGameObjects(float deltaTime)
{
	// first run the updateComponents method on each GameObject...
	for (std::vector<std::unique_ptr<GameObject>>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {

		GameObject* obj = (*it).get();
		obj->updateComponents(deltaTime);
	}

	// ...then run the lateUpdateComponents method on each GameObject
	for (std::vector<std::unique_ptr<GameObject>>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {

		GameObject* obj = (*it).get();
		obj->lateUpdateComponents(deltaTime);
	}
}

void GameWorld::teardownWorld()
{
	// todo
}
