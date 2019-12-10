#include "GameWorld.h"
#include "GameObject.h"

/*
	Initializes this Game World.
*/
GameWorld::GameWorld(std::string updateStrategy[], size_t n, float fixedDeltaTime)
	: gameObjects()
	, componentManager(updateStrategy, n)
	, fixedDeltaTime(fixedDeltaTime)
	, isPaused(false)
{
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	physicsWorld->setGravity(btVector3(0, -9.8, 0));	//gravity on Earth
	//physicsWorld->setDebugDrawer();
	//physicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
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

	delete dispatcher;
	delete collisionConfig;
	delete broadphase;
	delete solver;
	delete physicsWorld;
}

/*
	Adds a Game Object to this Game World's component collection.
*/
void GameWorld::addGameObject(GameObject* gameObject)
{
	const std::lock_guard<std::mutex> lock(mtx);

	gameObject->addToGameWorld(this);
	gameObjects.emplace(std::pair<std::string, GameObject*>(gameObject->id, gameObject));
}

/*
	Removes a Game Object from this Game World's component collection.
*/
bool GameWorld::removeGameObject(std::string id)
{
	const std::lock_guard<std::mutex> lock(mtx);

	if (gameObjects.find(id) == gameObjects.end())
	{
		return false;
	}

	delete gameObjects[id];
	gameObjects.erase(id);

	return true;
}

/*
	Calls the updateComponents() and fixedUpdate() functions of all Game Objects owned by this Game World, and steps the physics simulation.
*/
void GameWorld::updateGameObjects(float deltaTime)
{
	if (!isPaused)
	{
		int iterations = physicsWorld->stepSimulation(deltaTime, 1, fixedDeltaTime);

		for (int i = 0; i < iterations; ++i)
		{
			componentManager.fixedUpdate(fixedDeltaTime);
		}
	}

	componentManager.update(deltaTime);
}

/*
	Returns the GameObject associated to the given id.
*/
GameObject* GameWorld::getGameObjectById(std::string id)
{
	return gameObjects.at(id);
}

/*
	Stops the execution of updates.
*/
void GameWorld::pause()
{
	componentManager.pause();
	isPaused = true;

	for (auto& pair : gameObjects)
	{
		GameObject* obj = pair.second;
		obj->pause();
	}
}

/*
	Continues the execution of updates.
*/
void GameWorld::unpause()
{
	componentManager.unpause();
	isPaused = false;

	for (auto& pair : gameObjects)
	{
		GameObject* obj = pair.second;
		obj->unpause();
	}
}
