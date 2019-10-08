#pragma once

#include <string>
#include <unordered_map> 
#include "GameObject.h"

class GameWorld
{
public:
	btDynamicsWorld* physicsWorld;	//every physical object go to the world

	GameWorld();
	~GameWorld();
	void addGameObject(GameObject* gameObject);
	void removeGameObject(std::string id);
	void updateGameObjects(float deltaTime);
	void fixedUpdateGameObjects(float deltaTime);

private:
	std::unordered_map<std::string, GameObject*> gameObjects;

	// physics world stuff
	btDispatcher* dispatcher;	//what collision algorithm to use?
	btCollisionConfiguration* collisionConfig;	//what collision algorithm to use?
	btBroadphaseInterface* broadphase;	//should Bullet examine every object, or just what close to each other
	btConstraintSolver* solver;					//solve collisions, apply forces, impulses

};
