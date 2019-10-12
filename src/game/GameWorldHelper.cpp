#include "GameWorldHelper.h"
#include "../engine/BOEngine.h"
#include "../FileSystem.h"

void GameWorldHelper::initTestScene(BOEngine* engine, Shader* shader)
{
	std::cout << "Game init" << std::endl;

	// create suit man
	GameObject* suitMan = new GameObject("SuitMan");
	suitMan->addComponent(new RenderComponent(engine, "src/game/assets/nanosuit/nanosuit.obj", shader)); // connect object - model
	suitMan->transform.scale = Vector3f(0.2f, 0.2f, 0.2f);
	suitMan->addComponent(RigidBodyComponent::createWithCylinder(0.75, 1.5, 0.25, 0, 20, 0, 1.0, 45, 45, 45)); // connect object - rigibody
	engine->gameWorld.addGameObject(suitMan); // maybe auto register?

	// create ground
	GameObject* ground = new GameObject("Ground");
	ground->addComponent(new RenderComponent(engine, "src/game/assets/ground/plane.obj", shader));
	ground->addComponent(RigidBodyComponent::createWithPlane(0, -3.25, 0));
	engine->gameWorld.addGameObject(ground);

	ground->transform.scale = Vector3f(100.0f, 1.0f, 100.0f);

	// create box
	string osPathBox;
	FileSystem::BuildOSPath(FileSystem::FindFile("game/assets/box/cube.obj"), "game/assets/box/cube.obj", osPathBox);
	GameObject* box = new  GameObject("Box");
	box->addComponent(new RenderComponent(engine, osPathBox, shader));
	box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 5.0, 10.0, 0, 1.0, 0, 0, 0));
	engine->gameWorld.addGameObject(box);

	box->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge

	GameObject* box2 = new  GameObject("Box2");
	box2->addComponent(new RenderComponent(engine, osPathBox, shader));
	box2->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 5.0, 15.0, 0, 1.0, 0, 0, 0));
	engine->gameWorld.addGameObject(box2);

	box2->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge

	GameObject* box3 = new  GameObject("Box3");
	box3->addComponent(new RenderComponent(engine, osPathBox, shader));
	box3->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0, 0, 0, 0));
	engine->gameWorld.addGameObject(box3);

	box3->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge

	GameObject* box4 = new  GameObject("Box4");
	box4->addComponent(new RenderComponent(engine, osPathBox, shader));
	box4->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 5.0, 25.0, 0, 1.0, 0, 0, 0));
	engine->gameWorld.addGameObject(box4);

	box4->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
}
