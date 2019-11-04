#include "GameWorld.h"
#include "GameObject.h"

/*
	Initializes this Game World.
*/
GameWorld::GameWorld(std::string updateStrategy[], size_t n)
	: gameObjects()
	, componentManager(updateStrategy, n)
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
}

/*
	Adds a Game Object to this Game World's component collection.
*/
void GameWorld::addGameObject(GameObject* gameObject)
{
	gameObject->addToGameWorld(this);
	gameObjects.emplace(std::pair<std::string, GameObject*>(gameObject->id, gameObject));
}

/*
	Removes a Game Object from this Game World's component collection.
*/
bool GameWorld::removeGameObject(std::string id)
{
	if (gameObjects.find(id) == gameObjects.end())
	{
		return false;
	}

	delete gameObjects[id];
	gameObjects.erase(id);

	return true;
}

/*
	Calls the updateComponents() and lateUpdateComponents() functions of all Game Objects owned by this Game World.
*/
void GameWorld::updateGameObjects(float deltaTime)
{
	componentManager.update(deltaTime);
}

/*
	Calls the fixedUpdateComponents() function of all Game Objects owned by this Game World.
*/
void GameWorld::fixedUpdateGameObjects(float deltaTime)
{
	physicsWorld->stepSimulation(deltaTime);
	//physicsWorld->debugDrawWorld();
	componentManager.fixedUpdate(deltaTime);
}
