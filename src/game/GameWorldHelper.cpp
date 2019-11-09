#include "GameWorldHelper.h"
#include "../engine/BOEngine.h"
#include "../engine/ECS/ComponentManager.h"
#include "../src/game/components/AudioPlayerComponent.h"
#include "components/TypeTestComponent.h"
#include "components/CarControlComponent.h"

/*
	Loads a test scene into the given BOEngine.
*/
void GameWorldHelper::initTestScene(BOEngine* engine)
{
	// std::cout << "Game init" << std::endl;

	Shader * shader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/model_loading.fs");

	Shader* lightshader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/light.fs.glsl");

	shader->use();
	shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f); //obj to light
	shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader->setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(16.0f,  5.0f,  0.0f),
		glm::vec3(12.3f, 5.3f, 5.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// point light 1
	shader->setVec3("pointLights[0].position", pointLightPositions[0]);
	shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	shader->setVec3("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	shader->setFloat("pointLights[0].constant", 1.0f);
	shader->setFloat("pointLights[0].linear", 0.09);
	shader->setFloat("pointLights[0].quadratic", 0.032);

	// point light 2
	shader->setVec3("pointLights[1].position", pointLightPositions[1]);
	shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	shader->setVec3("pointLights[1].diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	shader->setFloat("pointLights[1].constant", 1.0f);
	shader->setFloat("pointLights[1].linear", 0.09);
	shader->setFloat("pointLights[1].quadratic", 0.032);

	std::string strategy[] = {CarControlComponent::typeID, RigidBodyComponent::typeID, RenderComponent::typeID};
	engine->gameWorld = new GameWorld(strategy, 3);

	Vector3f carPos = Vector3f(15.0, 5.0, 0);
	GameObject* player_car = new  GameObject("PlayerCar");
	player_car->transform.position = carPos;
	player_car->transform.scale = 1;
	player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red_notires.obj", shader)); // no tires
	// player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red.obj", shader));
	player_car->addComponent(RigidBodyComponent::createWithCube(1.0, 0.3, 1.0, 1.0));
	CarControlComponent* carControl = new CarControlComponent();
	player_car->addComponent(carControl);
	engine->gameWorld->addGameObject(player_car);

	std::vector<GameObject*> tires(4);
	for (int i = 0; i < 4; i++) {
		tires[i] = new GameObject("PlayerCarTire" + i);
		tires[i]->parent = player_car;
		tires[i]->transform.position = Vector3f(1.55 * (i > 1 ? 1 : -1), 0.43, 1.02 * (i % 2 ? 1 : -1)); // relative local position, (back, up, left)
		if (!i % 2) { // right tires
			tires[i]->transform.rotation = Vector3f(0.0f, 3.1416, 0.0f);
		}
		tires[i]->transform.scale = 1;
		tires[i]->addComponent(new RenderComponent(engine, "game/assets/avent/Tires.obj", shader));
		((RenderComponent*)tires[i]->getComponent<RenderComponent>())->isSelfRotation = true;
		engine->gameWorld->addGameObject(tires[i]);
	}
	carControl->tires = tires;

	//background music
	GameObject* background_music = new  GameObject("BackGroundMusic");
	engine->gameWorld->addGameObject(background_music);
	background_music->addComponent(new AudioPlayerComponent("game/assets/sounds/start.mp3", 1, false, true, false));
	background_music->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	background_music->getComponent<AudioPlayerComponent>()->volume(0.5);
	background_music->getComponent<AudioPlayerComponent>()->play();


	// create suit man
	GameObject* suitMan = new GameObject("SuitMan");
	suitMan->transform.position = Vector3f(0, 20, 0);
	suitMan->transform.rotation = Vector3f(45, 45, 45);
	suitMan->transform.scale = Vector3f(0.2f, 0.2f, 0.2f);
	suitMan->addComponent(new RenderComponent(engine, "game/assets/nanosuit/nanosuit.obj", shader)); // connect object - model
	suitMan->addComponent(RigidBodyComponent::createWithCylinder(0.75, 1.5, 0.25, 1.0)); // connect object - rigibody
	engine->gameWorld->addGameObject(suitMan); // maybe auto register?

	suitMan->addComponent(new AudioPlayerComponent("game/assets/sounds/startup.wav", 30, true, false, false));
	suitMan->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	suitMan->getComponent<AudioPlayerComponent>()->play();
	Sleep(2000);
	suitMan->addComponent(new AudioPlayerComponent("game/assets/sounds/idle.wav", 20, true, true, false));
	suitMan->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	suitMan->getComponent<AudioPlayerComponent>()->setSpeed(0);
	suitMan->getComponent<AudioPlayerComponent>()->play();


	// create race track
	GameObject* raceTrack = new GameObject("RaceTrack");
	raceTrack->transform.position = Vector3f(0, -3.2, 0);
	raceTrack->transform.rotation = Vector3f(0, 0, 0);
	raceTrack->transform.scale = Vector3f(1.0, 1.0, 1.0);
	raceTrack->addComponent(new RenderComponent(engine, "game/assets/racetrack/racetrack.obj", shader)); // connect object - model
	raceTrack->addComponent(RigidBodyComponent::createWithMesh(&raceTrack->getComponent<RenderComponent>()->model, 0.0)); // connect object - rigibody
	engine->gameWorld->addGameObject(raceTrack); // maybe auto register?

	// Light
	GameObject* light = new  GameObject("Light");
	light->transform.position = Vector3f(pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
	light->transform.scale = 1.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	light->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", lightshader));
	// box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld->addGameObject(light);

	// Light
	GameObject* light2 = new  GameObject("Light1");
	light2->transform.position = Vector3f(pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	light2->transform.scale = 1.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	light2->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", lightshader));
	// box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld->addGameObject(light2);

	// create ground
	GameObject* ground = new GameObject("Ground");
	ground->transform.position = Vector3f(0, -3.25, 0);
	ground->transform.scale = Vector3f(100.0f, 1.0f, 100.0f);
	ground->addComponent(new RenderComponent(engine, "game/assets/ground/plane.obj", shader));
	ground->addComponent(RigidBodyComponent::createWithPlane());
	engine->gameWorld->addGameObject(ground);

	// create box
	GameObject* box = new  GameObject("Box");
	box->transform.position = Vector3f(5.0, 10.0, 0);
	box->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", shader));
	box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld->addGameObject(box);

	GameObject* box2 = new  GameObject("Box2");
	box2->transform.position = Vector3f(5.0, 15.0, 0);
	box2->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box2->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", shader));
	box2->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld->addGameObject(box2);


	GameObject* box3 = new  GameObject("Box3");
	box3->transform.position = Vector3f(5.0, 20.0, 0);
	box3->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box3->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", shader));
	box3->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	engine->gameWorld->addGameObject(box3);

	GameObject* box4 = new  GameObject("Box4");
	box4->transform.position = Vector3f(5.0, 25.0, 0);
	box4->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box4->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", shader));
	box4->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
	box4->addComponent(new TypeTestComponent("This is a test message!"));
	engine->gameWorld->addGameObject(box4);

	box4->getComponent<TypeTestComponent>()->talk();
}
