#include "GameWorld.h"
#include "GameObject.h"

GameWorld::GameWorld()
	: gameObjects(5)
{
}

void GameWorld::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObjects.push_back(std::move(gameObject));
}

void GameWorld::removeGameObject(std::string id)
{
	// todo
}

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
