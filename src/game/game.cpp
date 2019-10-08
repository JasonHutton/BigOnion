#include "game.h"
#include "../FileSystem.h"

void Game::init(BOEngine* engine, Shader* shader)
{
	std::cout << "Game init" << std::endl;

	// create suit man
	GameObject* suitMan = new GameObject("SuitMan");
	suitMan->addComponent(new RenderComponent(engine, "src/game/assets/nanosuit/nanosuit.obj", shader)); // connect object - model
	suitMan->transform.position = Vector3f(0.0f, 10.f, 0.0f);
	suitMan->transform.scale = Vector3f(0.2f, 0.2f, 0.2f);
	suitMan->transform.rotation = Vector3f(3.14f, 3.14f, 0.0f);

	suitMan->addComponent(new RigidBodyComponent(addCylinder(0.75, 1.5, 0.25, 0, 20, 0, 1.0))); // connect object - rigibody
	engine->gameWorld.addGameObject(suitMan); // maybe auto register?

	// create ground
	GameObject* ground = new GameObject("Ground");
	ground->addComponent(new RenderComponent(engine, "src/game/assets/ground/plane.obj", shader));
	ground->addComponent(new RigidBodyComponent(addPlane(0, -3.25, 0)));
	engine->gameWorld.addGameObject(ground);

	ground->transform.position = Vector3f(0, -3.25, 0);
	ground->transform.scale = Vector3f(100.0f, 1.0f, 100.0f);

	// create box
	string osPathBox;
	FileSystem::BuildOSPath(FileSystem::FindFile("game/assets/box/cube.obj"), "game/assets/box/cube.obj", osPathBox);
	GameObject* box = new  GameObject("Box");
	box->addComponent(new RenderComponent(engine, osPathBox, shader));
	box->addComponent(new RigidBodyComponent(addCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0)));
	engine->gameWorld.addGameObject(box);

	box->transform.position = Vector3f(5.0, 30, 0);
	box->transform.scale = 2.5;

	// create box without physics
	GameObject* boxWithoutBt = new  GameObject("boxWithoutBt");
	boxWithoutBt->addComponent(new RenderComponent(engine, "src/game/assets/box/cube.obj", shader));
	// boxWithoutBt->addComponent(new RigidBodyComponent(addCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0)));
	engine->gameWorld.addGameObject(boxWithoutBt);

	boxWithoutBt->transform.position = Vector3f(0.0, 0.2, -2);
	boxWithoutBt->transform.scale = 1.5;

}

btRigidBody* Game::addCube(float width, float height, float depth, float x, float y, float z, float mass)
{
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btBoxShape* box = new btBoxShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		box->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself
	return body;
}

btRigidBody* Game::addPlane(float x, float y, float z) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);
	return body;
}

btRigidBody* Game::addCylinder(float width, float height, float depth, float x, float y, float z, float mass) {
	btTransform t;	//position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));	//put it to x,y,z coordinates
	btCylinderShape* cylinder = new btCylinderShape(btVector3(width, height, depth));
	btVector3 inertia(0, 0, 0);	//inertia is 0,0,0 for static object, else
	if (mass != 0.0)
		cylinder->calculateLocalInertia(mass, inertia);	//it can be determined by this function (for all kind of shapes)

	btMotionState* motion = new btDefaultMotionState(t);	//set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cylinder, inertia);	//create the constructioninfo, you can create multiple bodies with the same info
	btRigidBody* body = new btRigidBody(info);	//let's create the body itself
	return body;
}
