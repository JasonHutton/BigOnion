#include "game_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // stb_image can only be included in cpp instead of header.

#include "../src/engine/audio/AudioEngine.h"
#include "../engine/BOEngine.h"
#include "../../Settings.h"
#include "../engine/input/GameInput.h"

#include <GLFW/glfw3.h>
#include <ctime>

#include "imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "components/RaceGameComponent.h"
#include "GameWorldHelper.h"

// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void updateListener();
void calculateSpeed(float deltaTime);
void accelSound(GameObject* object);
void Wait(GameObject* object, bool isPlaying, float deltaTime, float wait, int mode);
// camera
Camera* camera;
AudioEngine audio;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// level control
int current_level = 1; // may be larger than max
const int max_level = 2;

//listener
Vector3 position{ 0,0,0 };
Vector3 rotation{ 0,0,0 };
Vector3 up{ 0,0,0 };
Vector3 vel{ 0,0,0 };

// Music Toggle

bool MusicToggle = true;
int MusicSlider = 3;

bool show_demo_window = true;
bool show_another_window = false;
bool show_GameMenu_window = true;//
bool show_HighScore_window = false;
bool game_loaded = false;
bool stopgame = true;
bool gamewin = false;
bool gamelost = false;
bool isPressing = false;
int stopcase = 0;
bool showmouse = true;
int mousecase = 0;
float speed = 0;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool isPlaying = false;
bool skidSound = false;
bool impactS = false;
bool impactB = false;
float timeImpactS = 0;
float timeImpactB = 0;
float timeSkid = 0;
bool recordtime = true;
int timego;
int starttime;
int temp = 0;
int oldtimego = 0;
bool timing;
int differ;
bool firstStart = true;

GameLoader::GameLoader()
{

}

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;
	return true;
}

bool callbackFunc(btManifoldPoint& cp, void* body0, void* body1)
{
	btCollisionObject* colObj0Wrap = static_cast<btCollisionObject*>(body0);
	btCollisionObject* colObj1Wrap = static_cast<btCollisionObject*>(body1);

	RigidBodyComponent* rbc0 = static_cast<RigidBodyComponent*>(colObj0Wrap->getUserPointer());
	RigidBodyComponent* rbc1 = static_cast<RigidBodyComponent*>(colObj1Wrap->getUserPointer());
	if (rbc0->isHit(rbc1))
	{
		if (speed > 120)
		{
			impactB = true;
		}
		else
		{
			impactS = true;
		}
		calculateSpeed(-0.08);
	}
	if (rbc1->isHit(rbc0))
	{
		if (speed > 120)
		{
			impactB = true;
		}
		else
		{
			impactS = true;
		}
		calculateSpeed(-0.08);
	}

	return false;
}

void GameLoader::createGame() {

	std::cout << "createGame" << std::endl;

	gContactProcessedCallback = callbackFunc;

}

void GameLoader::loadGameScene() {
	GameInput::setVerticalAxis(0);
	GameInput::setHorizontalAxis(0);

	game_loaded = true;
	if (current_level == 1)
		GameWorldHelper::initTestScene(engine);
	else {
		GameWorldHelper::initTestScene2(engine);
	}
}

void GameLoader::startGame() {

	GameWorldHelper::initMenuScene(engine);

	std::cout << "startGame" << std::endl;
	// glfw window creation
	// --------------------
	GLFWwindow* window = engine->window;
	camera = &engine->camera;

	int my_image_width = 404;
	int my_image_height = 404;
	GLuint my_image_texture = 0;
	GLuint my_image_texture1 = 0;
	//background img
	bool ret = LoadTextureFromFile("src\\game\\assets\\img\\racing.jpg", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);

	// inputs

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	engine->preRender();

	glfwSetTime(0);

	float racePercentage = 0, lastRacePercentage = 0;
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{


		float currentFrame = (float)glfwGetTime(); // We should probably be using double instead of float, but that's spawning off a LOT of required changes...
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		// input
		// -----
		if (!stopgame) {
			processInput(window);
		}
		else {
			// clear last gameinput state
			GameInput::clearState();
		}

		// game logic
		GameObject* playerCar = nullptr;
		if (game_loaded) {
			playerCar = engine->gameWorld->getGameObjectById("PlayerCar");

			if (playerCar) {
				// update third person camera
				glm::vec3 rot = playerCar->transform.rotation.getGlmVec3();
				glm::vec3 pos = playerCar->transform.position.getGlmVec3() + glm::vec3(0.0f, 1.15f, 0.0f); // look a few upper
				engine->tpCamera.update(deltaTime, playerCar->transform.position.getGlmVec3(), rot);

				// update percentage
				racePercentage = playerCar->getComponent<RaceGameComponent>()->GetPercentage();
				if (lastRacePercentage != racePercentage)
				{
					printf("Game finished %f percent \n", racePercentage * 100.0f);
					lastRacePercentage = racePercentage;
				}
			}
		}
		GameObject* engineSound = engine->gameWorld->getGameObjectById("EngineSound");
		GameObject* skid = engine->gameWorld->getGameObjectById("SkidSound");
		GameObject* impactBig = engine->gameWorld->getGameObjectById("BigImpact");
		GameObject* impactSmall = engine->gameWorld->getGameObjectById("SmallImpact");
		GameObject* background_music = engine->gameWorld->getGameObjectById("BackgroundMusic");

		if (MusicToggle == true)
		{
			background_music->getComponent<AudioPlayerComponent>()->play();
		}
		
		if (speed > 10)
		{
			if (impactB)
			{
				impactBig->getComponent<AudioPlayerComponent>()->play();
			}
			if (impactS)
			{
				impactSmall->getComponent<AudioPlayerComponent>()->play();
			}
		}

		Wait(impactSmall, impactS, deltaTime, 0.3, 1);
		Wait(impactBig, impactB, deltaTime, 1.6, 2);
		Wait(skid, skidSound, deltaTime, 1.2, 0);
		engine->updateEngine(deltaTime);
		calculateSpeed(-deltaTime);
		accelSound(engineSound);
		updateListener();
		audio.Set3dListenerAndOrientation(position, { 0 }, up, rotation);
		//printf("Camera Position: %f, %f, %f \n", playerCar->transform.position.x, playerCar->transform.position.y, playerCar->transform.position.z);
		//playerCar->getComponent<AudioPlayerComponent>()->update(deltaTime);

		//}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		if (showmouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);                         // show mouse
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		glfwPollEvents();

		int windowW = engine->gwidth;
		int windowH = engine->gHeight;

		//new Imgui frame
		ImGui_ImplGlfwGL3_NewFrame();
		//ImGuiWindowFlags flags = ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;//no title bar and fixed window size
		//************ Show Mouse*********************
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Tab))) {
			switch (mousecase)
			{
			case 0:
				showmouse = false;
				mousecase = 1;
				break;
			case 1:
				showmouse = true;
				mousecase = 0;
				break;
			}

		}
		//************HUD: Time*********************


		ImGui::SetNextWindowSize(ImVec2(windowW, windowH));        //window size
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));     //window position
		ImGui::StyleColorsLight();
		ImGui::Begin("Time", 0, flags);

		if (recordtime) {
			starttime = int(glfwGetTime());
		}

		if (show_GameMenu_window == false && show_HighScore_window == false) {

			recordtime = false;
			timego = currentFrame - starttime;
			if (timego <= 5) {

				//CalcTextSize
				ImVec2 timeW = ImGui::CalcTextSize("The game starts in % .d second", NULL, true);
				ImVec2 firetW = ImGui::CalcTextSize("Hi BIG Onion", NULL, true);
				ImVec2 secondW = ImGui::CalcTextSize("Are you ready?", NULL, true);
				
				ImVec2 thirdW = ImGui::CalcTextSize("Let's GO.", NULL, true);
				ImGui::SetCursorPos(ImVec2((windowW / 2) - (timeW.x / 2), 200.0f));
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "The game starts in %.d second", 6 - timego);

				switch (timego) {
				case 0:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (firetW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Hi BIG Onion");
					break;
				case 1:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (firetW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Hi BIG Onion");
					break;
				case 2:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (secondW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Are you ready?");
					break;
				case 3:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (secondW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Are you ready?");
					break;
				case 4:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (secondW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Are you ready?");
					break;
				case 5:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (thirdW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Let's GO.");
					break;

				}

			}
			if (timego > 5) {
				
				stopgame = false;
				ImGui::SetCursorPos(ImVec2((windowW / 2), 200.0f));

				if (timing) {
					temp = 66 - (timego - differ);
				}
				if (temp == 0) {
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "0");
				}
				if (stopcase == 0) {
					timing = true;
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%.d", temp);
				}
				if (stopcase == 1) {
					timing = false;
					if (!timing) {
						oldtimego = 66 - temp;
					}
					differ = timego - oldtimego;
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%.d", temp);
				}
			}
		}

		ImGui::End();

		//************HUD: Score*********************
		ImGui::SetNextWindowSize(ImVec2(200, 100));        //window size

		ImGui::SetNextWindowPos(ImVec2(0, windowH - 100));     //window position
		ImGui::StyleColorsDark();

		ImGui::Begin("Score", 0, flags);

		int score1 = 100;

		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Score: %.d", score1);
		ImGui::End();

		//***************HUD: Speed******************

		ImGui::SetNextWindowSize(ImVec2(200, 100));
		ImGui::SetNextWindowPos(ImVec2(windowW - 200, windowH - 100));
		ImGui::StyleColorsDark();

		ImGui::Begin("Speed", 0, flags);

		if (stopcase == 1) {
			speed = 0;
		}

		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Speed:%d km/h", (int)speed);
		ImGui::End();

		//***************HUD: stop game***************

		//ImGui::SetNextWindowSize(ImVec2(200, 80));
		ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::StyleColorsLight();
		ImGui::Begin("Pause", 0, flags);
		if (ImGui::Button("Pause", ImVec2(200.0f, 60.0f))) // press stop to stop player movement
		{

			switch (stopcase) {
			case 0:
				engine->gameWorld->pause();
				stopcase = 1;

				break;
			case 1:
				engine->gameWorld->unpause();
				stopcase = 0;

				break;
			}
		}
		ImGui::End();

		//*************HUD: Back Game Menu*****************

		ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

		ImGui::Begin("Pause", 0, flags);
		ImGui::StyleColorsLight();

		if (stopcase) {
			if (ImGui::Button("Back to Menu", ImVec2(200.0f, 60.0f)))
			{
				show_GameMenu_window = true;
			}
		}


		ImGui::End();


		//***************Game Main Menu****************

		if (show_GameMenu_window)
		{
			GameObject* background_music = engine->gameWorld->getGameObjectById("BackgroundMusic");

			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("Big Onion", &show_GameMenu_window, flags);
			my_image_width = windowW;
			my_image_height = windowH;
			ImGui::Image((void*)(intptr_t)my_image_texture1, ImVec2(my_image_width * 0.125, my_image_height * 0.125));
			ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));

			ImGui::SetCursorPos(ImVec2((windowW / 1) - (windowW / 1.85), 200.0f));
			ImGui::Text("Big Onion", ImVec2(windowW / 2, 50.0f));

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 300.0f));
			//if (ImGui::Button("Play Game", ImVec2(-1.0f, 0.0f)))
			if (ImGui::Button("Play Game", ImVec2(windowW / 2, 50.0f))) {
				show_GameMenu_window = false;
				current_level = 1;
				reload();
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 400.0f));
			if (ImGui::Button("Load Game", ImVec2(windowW / 2, 50.0f))) {
				show_GameMenu_window = false;
				reload();	
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 500.0f));
			if (ImGui::Button("High Score", ImVec2(windowW / 2, 50.0f)))
			{
				show_GameMenu_window = false;
				show_HighScore_window = true;
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 20), 600.0f));
			if (ImGui::Checkbox("Music Toggle", &MusicToggle))
			{
				if (!MusicToggle)
				{
					background_music->getComponent<AudioPlayerComponent>()->pause();
				}
				else
				{
					background_music->getComponent<AudioPlayerComponent>()->play();
				}
			}

			ImGui::SetCursorPos(ImVec2((windowW / 6), 650.0f));
			if (ImGui::SliderInt("Volume", &MusicSlider, 1, 5))
			{
				background_music->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 750.0f));
			if (ImGui::Button("Exit", ImVec2(windowW / 2, 50.0f)))
				break;
			ImGui::End();

		}
		//**********High score list Window************
		static const char* scores[]{ "1","2","3","4","5","6","7","8","9","10" };//high score list
		static int selectscore = 0;

		if (show_HighScore_window)
		{
			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("highscore", &show_HighScore_window, flags);
			ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
			if (ImGui::Button("Back", ImVec2(200.0f, 60.0f)))
			{
				show_HighScore_window = false;
				show_GameMenu_window = true;
			}
			ImGui::End();

			ImGui::SetNextWindowSize(ImVec2(windowW / 2, windowH / 2));
			ImGui::SetNextWindowPos(ImVec2(windowW / 2 - windowW / 3.3, windowH / 2 - windowH / 3.3));
			ImGui::Begin("highscore", &show_HighScore_window, flags);

			ImVec2 scoreW = ImGui::CalcTextSize("High Score", NULL, true);
			ImGui::SetCursorPos(ImVec2((windowW / 3.3) - (scoreW.x / 2), 0.0f));
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "High Score");

			ImGui::ListBox("", &selectscore, scores, IM_ARRAYSIZE(scores));
			ImGui::End();
		}
		//***********win window******************

		if (racePercentage * 100.0f >= 100 && !gamewin) {
			gamewin = true;
			playerCar->getComponent<RaceGameComponent>()->resetPercentage();
			current_level += (current_level > max_level) ? 0 : 1;
		}
		if (gamewin)
		{
			GameObject* background_music = engine->gameWorld->getGameObjectById("BackgroundMusic");
			GameObject* win1 = engine->gameWorld->getGameObjectById("WinMusic1");
			GameObject* win2 = engine->gameWorld->getGameObjectById("WinMusic2");

			if (!isPlaying)
			{
				if (rand() % 1 == 0)
				{
					background_music->getComponent<AudioPlayerComponent>()->pause();
					win1->getComponent<AudioPlayerComponent>()->play();
					win1->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
					isPlaying = true;
				}
				else
				{
					background_music->getComponent<AudioPlayerComponent>()->pause();
					win2->getComponent<AudioPlayerComponent>()->play();
					win2->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
					isPlaying = true;
				}
			}
			stopgame = true;
			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("win", &gamewin, flags);

			ImVec2 winW = ImGui::CalcTextSize("Your Win", NULL, true);
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (winW.x / 2), 50.0f));
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "You Win");

			ImVec2 scoreW = ImGui::CalcTextSize("Your score:   ", NULL, true);
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (scoreW.x / 2), 100.0f));
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Score: %.d", score1);

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 200.0f));
			if (ImGui::Button("Try Again", ImVec2(windowW / 2, 50.0f))) {
				current_level--;
				reload();
				gamewin = false;
				isPlaying = false;
			}

			if (current_level <= max_level) {
				ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 300.0f));                 //next level
				if (ImGui::Button("Next Level", ImVec2(windowW / 2, 50.0f))) {
					reload();
					gamewin = false;
					isPlaying = false;
				}
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 600.0f));
			if (ImGui::Button("Back to Menu", ImVec2(windowW / 2, 50.0f))) {
				gamewin = false;
				show_GameMenu_window = true;
				isPlaying = false;
				win1->getComponent<AudioPlayerComponent>()->pause();
				win2->getComponent<AudioPlayerComponent>()->pause();
				background_music->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
			}

			ImGui::End();
			//std::string pi = std::to_string(100);
			//scores[0] = (char*)pi.data();

		}

		//***********lost window******************
		if (temp < 0) {
			gamelost = true;
		}
		if (gamelost && !gamewin)
		{
			GameObject* background_music = engine->gameWorld->getGameObjectById("BackgroundMusic");
			GameObject* lose1 = engine->gameWorld->getGameObjectById("LoseMusic1");
			GameObject* lose2 = engine->gameWorld->getGameObjectById("LoseMusic2");

			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("lost", &gamelost, flags);

			if (!isPlaying)
			{
				if (rand() % 1 == 0)
				{
					background_music->getComponent<AudioPlayerComponent>()->pause();
					lose1->getComponent<AudioPlayerComponent>()->play();
					lose1->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
					isPlaying = true;
				}
				else
				{
					background_music->getComponent<AudioPlayerComponent>()->pause();
					lose2->getComponent<AudioPlayerComponent>()->play();
					lose2->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
					isPlaying = true;
				}
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 100.0f));
			if (ImGui::Button("Restart Game", ImVec2(windowW / 2, 50.0f))) {
				gamelost = false;
				reload();
				isPlaying = false;
			}
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 200.0f));
			if (ImGui::Button("Back to Menu", ImVec2(windowW / 2, 50.0f))) {
				gamelost = false;
				show_GameMenu_window = true;
				isPlaying = false;
				lose1->getComponent<AudioPlayerComponent>()->pause();
				lose2->getComponent<AudioPlayerComponent>()->pause();
				background_music->getComponent<AudioPlayerComponent>()->volume((float)MusicSlider * 0.1);
			}
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	//            return 0;
}

void Wait(GameObject* object, bool isPlaying, float deltaTime, float wait, int mode)
{
	if (mode == 0)
	{
		if (timeSkid > wait)
		{
			skidSound = false;
			timeSkid = 0;
			object->getComponent<AudioPlayerComponent>()->pause();
		}
		if (isPlaying)
		{
			timeSkid = timeSkid + deltaTime;
		}
	}
	if (mode == 1)
	{
		if (timeImpactS > wait)
		{
			impactS = false;
			timeImpactS = 0;
			object->getComponent<AudioPlayerComponent>()->pause();
		}
		if (isPlaying)
		{
			timeImpactS = timeImpactS + deltaTime;
		}
	}
	if (mode == 2)
	{
		if (timeImpactB > wait)
		{
			impactB = false;
			timeImpactB = 0;
			object->getComponent<AudioPlayerComponent>()->pause();
		}
		if (isPlaying)
		{
			timeImpactB = timeImpactB + deltaTime;
		}
	}
}

//Update Listener Position and Orientation
void updateListener()
{
	position.x = camera->Position.x;
	position.y = camera->Position.y;
	position.z = camera->Position.z;
	rotation.x = camera->Front.x;
	rotation.y = camera->Front.y;
	rotation.z = camera->Front.z;
	up.x = camera->Up.x;
	up.y = camera->Up.y;
	up.z = camera->Up.z;
}

void calculateSpeed(float deltaTime)
{
	if (deltaTime >= 0)
	{
		if (speed < 200)
		{
			speed = speed + deltaTime * 10;
		}
	}
	else
	{
		if (speed < 0)
		{
			speed = 0;
		}
		else if (speed < 10)
		{
			speed = speed + deltaTime * 10;
		}
		else if (speed < 50)
		{
			speed = speed + deltaTime * 20;
		}
		else if (speed < 100)
		{
			speed = speed + deltaTime * 40;
		}
		else if (speed < 150)
		{
			speed = speed + deltaTime * 60;
		}
		else if (speed < 201)
		{
			speed = speed + deltaTime * 80;
		}
	}
}

void accelSound(GameObject* object)
{
	if (speed >= 0)
	{
		object->getComponent<AudioPlayerComponent>()->setSpeed(speed);
	}
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GameLoader::processInput(GLFWwindow* window)
{
	// clear last gameinput state
	GameInput::clearState();
	GameObject* skid = engine->gameWorld->getGameObjectById("SkidSound");
	// Check all bound controls
	for (map<int, keyState>::iterator it = input.GetAllKeyStates().begin(); it != input.GetAllKeyStates().end(); it++)
	{
		// If the bound control is being pressed....
		if (glfwGetKey(window, it->first) == GLFW_PRESS)
		{
			// See if a bound control has a User Button associated with it.
			ContextControl cc = input.GetControl(it->first);
			// Do what the context control->User Button says to do.
			switch (cc.GetControl("")) // Default context.
			{
			case UB_FORCE_QUIT:
				glfwSetWindowShouldClose(window, true);
				break;
			case UB_MOVE_FORWARD:
				//camera->ProcessKeyboard(FORWARD, deltaTime);
				GameInput::setVerticalAxis(-1.0);
				calculateSpeed(0.04);
				break;
			case UB_MOVE_BACKWARD:
				//camera->ProcessKeyboard(BACKWARD, deltaTime);
				GameInput::setVerticalAxis(1.0);
				calculateSpeed(-0.04);
				if (speed > 10)
					skid->getComponent<AudioPlayerComponent>()->play();
				skidSound = true;
				break;
			case UB_MOVE_LEFT:
				//camera->ProcessKeyboard(LEFT, deltaTime);
				GameInput::setHorizontalAxis(1.0);
				calculateSpeed(-0.01);
				if (speed > 10)
					skid->getComponent<AudioPlayerComponent>()->play();
				skidSound = true;
				break;
			case UB_MOVE_RIGHT:
				//camera->ProcessKeyboard(RIGHT, deltaTime);
				GameInput::setHorizontalAxis(-1.0);
				calculateSpeed(-0.01);
				if (speed > 10)
					skid->getComponent<AudioPlayerComponent>()->play();
				skidSound = true;
				break;
			case UB_NONE:
			default:
				break;
			}

			/*switch (cc.GetControl("Menu")) // Some other context.
			{

			}*/
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		Settings::lastX = xpos;
		Settings::lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - Settings::lastX;
	double yoffset = Settings::lastY - ypos; // reversed since y-coordinates go from bottom to top

	Settings::lastX = xpos;
	Settings::lastY = ypos;

	camera->ProcessMouseMovement((float)xoffset, (float)yoffset); // We should probably be using double instead of float, but that's spawning off a LOT of required changes...

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll((float)yoffset); // We should probably be using double instead of float, but that's spawning off a LOT of required changes...
}

void GameLoader::setEngine(BOEngine& boe) {
	this->engine = &boe;
}

void GameLoader::reload() {
	recordtime = true;
	loadGameScene();
}

void GameLoader::exitGame() {

	std::cout << "exitGame" << std::endl;
}