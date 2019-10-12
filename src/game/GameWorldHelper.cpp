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
	box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 5.0, 20.0, 0, 1.0, 0, 0, 0));
	engine->gameWorld.addGameObject(box);

	box->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge

	// create box without physics
	GameObject* boxWithoutBt = new  GameObject("boxWithoutBt");
	boxWithoutBt->addComponent(new RenderComponent(engine, "src/game/assets/box/cube.obj", shader));
	engine->gameWorld.addGameObject(boxWithoutBt);

	boxWithoutBt->transform.position = Vector3f(0.0, 0.2, -2);
	boxWithoutBt->transform.scale = 1.5;

}
