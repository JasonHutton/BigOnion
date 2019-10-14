#include "GameWorldHelper.h"
#include "../engine/BOEngine.h"
#include "../FileSystem.h"

void GameWorldHelper::initTestScene(BOEngine* engine, Shader* shader)
{
	std::cout << "Game init" << std::endl;

	// create suit man
	GameObject* suitMan = new GameObject("SuitMan");
	suitMan->transform.position = Vector3f(0, 20, 0);
	suitMan->transform.rotation = Vector3f(45, 45, 45);
	suitMan->transform.scale = Vector3f(0.2f, 0.2f, 0.2f);
	suitMan->addComponent(new RenderComponent(engine, "src/game/assets/nanosuit/nanosuit.obj", shader)); // connect object - model
	suitMan->addComponent(RigidBodyComponent::createWithCylinder(0.75, 1.5, 0.25, 1.0)); // connect object - rigibody
	engine->gameWorld.addGameObject(suitMan); // maybe auto register?

	// create ground
	GameObject* ground = new GameObject("Ground");
	ground->transform.position = Vector3f(0, -3.25, 0);
	ground->transform.scale = Vector3f(100.0f, 1.0f, 100.0f);
	ground->addComponent(new RenderComponent(engine, "src/game/assets/ground/plane.obj", shader));
	ground->addComponent(RigidBodyComponent::createWithPlane());
	engine->gameWorld.addGameObject(ground);

	// create box
	string osPathBox;
	FileSystem::BuildOSPath(FileSystem::FindFile("game/assets/box/cube.obj"), "game/assets/box/cube.obj", osPathBox);
	GameObject* box = new  GameObject("Box");
	box->transform.position = Vector3f(5.0, 10.0, 0);
	box->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box->addComponent(new RenderComponent(engine, osPathBox, shader));
	box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld.addGameObject(box);

	GameObject* box2 = new  GameObject("Box2");
	box2->transform.position = Vector3f(5.0, 15.0, 0);
	box2->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box2->addComponent(new RenderComponent(engine, osPathBox, shader));
	box2->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld.addGameObject(box2);

	GameObject* box3 = new  GameObject("Box3");
	box3->transform.position = Vector3f(5.0, 20.0, 0);
	box3->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box3->addComponent(new RenderComponent(engine, osPathBox, shader));
	box3->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld.addGameObject(box3);

	GameObject* box4 = new  GameObject("Box4");
	box4->transform.position = Vector3f(5.0, 25.0, 0);
	box4->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box4->addComponent(new RenderComponent(engine, osPathBox, shader));
	box4->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld.addGameObject(box4);
}
