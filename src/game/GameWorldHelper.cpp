#include "GameWorldHelper.h"
#include "../engine/BOEngine.h"
#include "../engine/ECS/ComponentManager.h"
#include "../src/game/components/AudioPlayerComponent.h"
#include "components/TypeTestComponent.h"
#include "components/CarControlComponent.h"
#include "../../Settings.h"
#include "components/RaceGameComponent.h"

#include "../../Settings.h"

#include "yaml-cpp/yaml.h"
#include "../object_loader.h"
#include <vector>
#include "../engine/utils/ThreadPool.h"
#include <thread>

/*
	Loads a test scene into the given BOEngine.
*/
void GameWorldHelper::initTestScene(BOEngine* engine)
{
	auto start = std::chrono::steady_clock::now();
	// std::cout << "Game init" << std::endl;
	AudioEngine audio;
	Camera camera;
	Shader * shader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/model_loading.fs");

	Shader* lightshader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/light.fs.glsl");

	vector<std::string> faces
	{
		"game/assets/cmm_skybox/right.jpg",
		"game/assets/cmm_skybox/left.jpg",
		"game/assets/cmm_skybox/top.jpg",
		"game/assets/cmm_skybox/bottom.jpg",
		"game/assets/cmm_skybox/front.jpg",
		"game/assets/cmm_skybox/back.jpg"
	};

	engine->skybox.load(faces);

	shader->use();
	shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f); //obj to light
	shader->setVec3("dirLight.ambient", 0.35f, 0.35f, 0.35f);
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

	/* COMPONENT SETUP */

	// parallelization stuff
	auto threads = std::vector<std::thread*>();

	// create car
	threads.push_back(new std::thread([](BOEngine* engine, Shader* shader)
		{
			Vector3f carPos = Vector3f(0.0f, -3.0f, -43.0f);
			GameObject* player_car = new  GameObject("PlayerCar");
			player_car->transform.position = carPos;
			player_car->transform.rotation = Vector3f(0.0f, 0.0f, 0.0f);
			player_car->transform.scale = 1;
			player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red_notires.obj", shader)); // no tires
			// player_car->addComponent(new RenderComponent(engine, "game/assets/avent/Avent_red.obj", shader));
			player_car->addComponent(RigidBodyComponent::createWithCube(1.0, 0.4, 1.0, 1.0, 1.0, 0)); //note id is set to 0, DO NOT CHANGE unless you change the id in the isHit()
			CarControlComponent* carControl = new CarControlComponent(10, 15, 2.5);
			player_car->addComponent(carControl);
			player_car->addComponent(new RaceGameComponent());
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
		}, engine, shader));
	
	// sound thread
	threads.push_back(new std::thread([](BOEngine* engine, AudioEngine* audio, Camera* camera)
		{
			//engine sound
			GameObject* engine_sound = new  GameObject("EngineSound");
			engine_sound->transform.position = { camera->Position.x, camera->Position.y, camera->Position.z };
			engine->gameWorld->addGameObject(engine_sound);
			engine_sound->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/startup.wav", 1, true, false, false));
			engine_sound->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
			engine_sound->getComponent<AudioPlayerComponent>()->volume(1);
			engine_sound->getComponent<AudioPlayerComponent>()->play();
			engine_sound->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/idle.wav", 1, true, true, false));
			engine_sound->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
			engine_sound->getComponent<AudioPlayerComponent>()->volume(0.3);
			engine_sound->getComponent<AudioPlayerComponent>()->setSpeed(0);
			engine_sound->getComponent<AudioPlayerComponent>()->play();

			GameObject* skid_sound = new  GameObject("SkidSound");
			skid_sound->transform.position = { camera->Position.x, camera->Position.y, camera->Position.z };
			engine->gameWorld->addGameObject(skid_sound);
			skid_sound->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/car_break.mp3", 0.5, true, true, false));
			skid_sound->getComponent<AudioPlayerComponent>()->onAddToGameWorld();

			//impact sound
			GameObject* impact_sound_small = new  GameObject("SmallImpact");
			impact_sound_small->transform.position = { camera->Position.x, camera->Position.y, camera->Position.z };
			engine->gameWorld->addGameObject(impact_sound_small);
			impact_sound_small->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/small_impact.mp3", 30, true, true, false));
			impact_sound_small->getComponent<AudioPlayerComponent>()->onAddToGameWorld();

			GameObject* impact_sound_big = new  GameObject("BigImpact");
			impact_sound_big->transform.position = { camera->Position.x, camera->Position.y, camera->Position.z };
			engine->gameWorld->addGameObject(impact_sound_big);
			impact_sound_big->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/big_impact.mp3", 20, true, true, false));
			impact_sound_big->getComponent<AudioPlayerComponent>()->onAddToGameWorld();

			//background music
			GameObject* background_music = new  GameObject("BackgroundMusic");
			engine->gameWorld->addGameObject(background_music);
			background_music->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/start.mp3", 1, false, true, false));
			background_music->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
			background_music->getComponent<AudioPlayerComponent>()->volume(0.3, true);
			background_music->getComponent<AudioPlayerComponent>()->play();

			//win lose music
			GameObject* win1_music = new  GameObject("WinMusic1");
			engine->gameWorld->addGameObject(win1_music);
			win1_music->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/win1.mp3", 1, false, true, false));
			win1_music->getComponent<AudioPlayerComponent>()->onAddToGameWorld();

			GameObject* win2_music = new  GameObject("WinMusic2");
			engine->gameWorld->addGameObject(win2_music);
			win2_music->addComponent(new AudioPlayerComponent(*audio, "game/assets/sounds/win2.mp3", 1, false, true, false));
			win2_music->getComponent<AudioPlayerComponent>()->onAddToGameWorld();
		}, engine, &audio, &camera));

	// create race track walls
	threads.push_back(new std::thread([](BOEngine* engine, Shader* shader)
		{
			
			GameObject* trackWall = new GameObject("RaceTrackWalls");
			trackWall->transform.position = Vector3f(0, -3.25, 0);
			trackWall->transform.rotation = Vector3f(0, 0, 0);
			trackWall->transform.scale = Vector3f(1.0, 2.0, 1.0);
			//trackWall->addComponent(new RenderComponent(engine, "game/assets/track2/track_walls.obj", shader)); // connect object - model
			trackWall->addComponent(new RenderComponent(engine, "game/assets/track2/track_walls2.obj", shader)); // connect object - model
			trackWall->addComponent(RigidBodyComponent::createWithMesh(&trackWall->getComponent<RenderComponent>()->model, 1.0, 1));//note id is set to 1, DO NOT CHANGE unless you change the id in the isHit()
			engine->gameWorld->addGameObject(trackWall);
		}, engine, shader));

	// create race track
	threads.push_back(new std::thread([](BOEngine* engine, Shader* shader)
		{
			
			GameObject* raceTrack = new GameObject("RaceTrack");
			raceTrack->transform.position = Vector3f(0, -3.23, 0);
			raceTrack->transform.rotation = Vector3f(0, 0, 0);
			raceTrack->transform.scale = Vector3f(1.0, 1.0, 1.0);
			//raceTrack->addComponent(new RenderComponent(engine, "game/assets/track2/track_only.obj", shader)); // connect object - model
			raceTrack->addComponent(new RenderComponent(engine, "game/assets/track2/track_only2.obj", shader)); // connect object - model
			//raceTrack->addComponent(new RenderComponent(engine, "game/assets/racetrack/racetrack.obj", shader)); // connect object - model
			// raceTrack->addComponent(RigidBodyComponent::createWithMesh(&raceTrack->getComponent<RenderComponent>()->model)); // connect object - rigibody
			engine->gameWorld->addGameObject(raceTrack); // maybe auto register?
		}, engine, shader));
	

	// Light
	threads.push_back(new std::thread([](BOEngine* engine, glm::vec3* pointLightPositions, Shader* lightshader)
		{
			GameObject* light = new  GameObject("Light");
			light->transform.position = Vector3f(pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
			light->transform.scale = 1.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
			light->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", lightshader));
			// box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
			engine->gameWorld->addGameObject(light);
			
			GameObject* light2 = new  GameObject("Light1");
			light2->transform.position = Vector3f(pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
			light2->transform.scale = 1.0; // has to be double because dimensions of 1.0 entered above refer to distance from origin to edge
			light2->addComponent(new RenderComponent(engine, "game/assets/box/cube.obj", lightshader));
			// box->addComponent(RigidBodyComponent::createWithCube(1.0, 1.0, 1.0, 1.0));
			engine->gameWorld->addGameObject(light2);
		}, engine, pointLightPositions, lightshader));

	// create ground
	threads.push_back(new std::thread([](BOEngine* engine, Shader* shader)
		{
			GameObject* ground = new GameObject("Ground");
			ground->transform.position = Vector3f(0, -3.25, 0);
			ground->transform.scale = Vector3f(400.0f, 1.0f, 400.0f);
			ground->addComponent(new RenderComponent(engine, "game/assets/ground/plane.obj", shader));
			ground->addComponent(RigidBodyComponent::createWithPlane());
			engine->gameWorld->addGameObject(ground);

		}, engine, shader));

	
	// onion
	threads.push_back(new std::thread([](BOEngine* engine, Shader* shader)
		{
			engine->gameWorld->addGameObject(Object_Load("game/assets/objects/onion.yaml", engine, shader));
		}, engine, shader));
	

	// and to re-synchronize
	for (std::thread* thread : threads)
	{
		thread->join();
	}

	auto end = std::chrono::steady_clock::now();
	
	std::chrono::duration<float> duration = end - start;

	std::cout << "Loading complete! Took " << duration.count() << " seconds." << std::endl;
}
