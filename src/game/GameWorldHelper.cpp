#include "GameWorldHelper.h"
#include "../engine/BOEngine.h"
#include "../engine/ECS/ComponentManager.h"
#include "../src/game/components/AudioPlayerComponent.h"
#include "components/TypeTestComponent.h"
#include "components/CarControlComponent.h"
#include "../../Settings.h"
#include "components/RaceGameComponent.h"
/*
	Loads a test scene into the given BOEngine.
*/
void GameWorldHelper::initTestScene(BOEngine* engine)
{
	// std::cout << "Game init" << std::endl;
	AudioEngine audio;
	Shader * shader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/model_loading.fs");

	Shader* lightshader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/light.fs.glsl");

	shader->use();
	shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f); //obj to light
	shader->setVec3("dirLight.ambient", 0.15f, 0.15f, 0.15f);
	shader->setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader->setVec3("dirLight.specular", 0.8f, 0.8f, 0.8f);

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

	std::string strategy[] = {CarControlComponent::typeID, RigidBodyComponent::typeID, RenderComponent::typeID, RaceGameComponent::typeID };
	engine->gameWorld = new GameWorld(strategy, 4, 1.0 / 60.0);

	Vector3f carPos = Vector3f(0.0f, -3.0f, -43.0f);
	GameObject* player_car = new  GameObject("PlayerCar");
	player_car->transform.position = carPos;
	player_car->transform.rotation = Vector3f(0.0f, 0.0f, 0.0f);
	player_car->transform.scale = 1;
	player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red_notires.obj", shader)); // no tires
	// player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red.obj", shader));
	player_car->addComponent(RigidBodyComponent::createWithCube(1.0, 0.3, 1.0, 1.0, 1.0));
	CarControlComponent* carControl = new CarControlComponent(10, 15, 2.5);
	player_car->addComponent(carControl);
	player_car->addComponent(new RaceGameComponent());
	engine->gameWorld->addGameObject(player_car);
	player_car->addComponent(new AudioPlayerComponent(audio,"game/assets/sounds/startup.wav", 1, false, false, false));
	player_car->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	player_car->getComponent<AudioPlayerComponent>()->volume(0.3);
	player_car->getComponent<AudioPlayerComponent>()->play();
	Sleep(2000);
	player_car->addComponent(new AudioPlayerComponent(audio,"game/assets/sounds/idle.wav", 1, false, true, false));
	player_car->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	player_car->getComponent<AudioPlayerComponent>()->volume(0.05);
	player_car->getComponent<AudioPlayerComponent>()->setSpeed(0);
	player_car->getComponent<AudioPlayerComponent>()->play();


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
	/*GameObject* background_music = new  GameObject("BackgroundMusic");
	engine->gameWorld->addGameObject(background_music);
	background_music->addComponent(new AudioPlayerComponent(audio, "game/assets/sounds/start.mp3", 1, false, true, false));
	background_music->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
	background_music->getComponent<AudioPlayerComponent>()->volume(0.1);
	background_music->getComponent<AudioPlayerComponent>()->play();*/

	// create race track walls
	GameObject* trackWall = new GameObject("RaceTrackWalls");
	trackWall->transform.position = Vector3f(0, -3.25, 0);
	trackWall->transform.rotation = Vector3f(0, 0, 0);
	trackWall->transform.scale = Vector3f(1.0, 2.0, 1.0);
	trackWall->addComponent(new RenderComponent(engine, "game/assets/track2/track_walls.obj", shader)); // connect object - model
	trackWall->addComponent(RigidBodyComponent::createWithMesh(&trackWall->getComponent<RenderComponent>()->model, 1.0)); // connect object - rigibody
	engine->gameWorld->addGameObject(trackWall);

	// create race track
	GameObject* raceTrack = new GameObject("RaceTrack");
	raceTrack->transform.position = Vector3f(0, -3.1, 0);
	raceTrack->transform.rotation = Vector3f(0, 0, 0);
	raceTrack->transform.scale = Vector3f(1.0, 1.0, 1.0);
	raceTrack->addComponent(new RenderComponent(engine, "game/assets/track2/track_only.obj", shader)); // connect object - model
	//raceTrack->addComponent(new RenderComponent(engine, "game/assets/racetrack/racetrack.obj", shader)); // connect object - model
	// raceTrack->addComponent(RigidBodyComponent::createWithMesh(&raceTrack->getComponent<RenderComponent>()->model)); // connect object - rigibody
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

	/*GameObject* box4 = new  GameObject("Box4");
	box4->transform.position = Vector3f(5.0, 25.0, 0);
	box4->transform.scale = 2.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
	box4->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", shader));
	box4->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0, 0.0));
	box4->addComponent(new TypeTestComponent("This is a test message!"));
	engine->gameWorld->addGameObject(box4);

	box4->getComponent<TypeTestComponent>()->talk();*/
}
