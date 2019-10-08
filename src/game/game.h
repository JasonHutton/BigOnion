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
	void init(BOEngine* engine, Shader* shader);

	btRigidBody* addCube(float width, float height, float depth, float x, float y, float z, float mass);

	btRigidBody* addPlane(float x, float y, float z);

	btRigidBody* addCylinder(float width, float height, float depth, float x, float y, float z, float mass);

private:
	//TODO: move object to game
	
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
	
	std::vector<btRigidBody*> bodies;
};

