#pragma once

#include "../engine/BOEngine.h"
#include <btBulletDynamicsCommon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

class BOEngine;

class Game
{
public:
	Game();

	void init(BOEngine* engine);

	void updateWithDelta(float deltaTime);

	void render(BOEngine* engine);

	btRigidBody* addCube(float width, float height, float depth, float x, float y, float z, float mass);

	btRigidBody* addPlane(float x, float y, float z);

	btRigidBody* addCylinder(float width, float height, float depth, float x, float y, float z, float mass);

private:
	//TODO: move object to game
	Shader* modelShader = nullptr;
	Model* suitManModel = nullptr;
	Model* groundModel = nullptr;
	Model* boxModel = nullptr;
	Model* boxWithoutBtModel;

	GameObject* suitMan;
	GameObject* box;
	GameObject* ground;
	GameObject* boxWithoutBt;

	//physics stuff
	GLUquadricObj* quad;
	btDynamicsWorld* world;	//every physical object go to the world
	btDispatcher* dispatcher;	//what collision algorithm to use?
	btCollisionConfiguration* collisionConfig;	//what collision algorithm to use?
	btBroadphaseInterface* broadphase;	//should Bullet examine every object, or just what close to each other
	btConstraintSolver* solver;					//solve collisions, apply forces, impulses
	std::vector<btRigidBody*> bodies;
};

