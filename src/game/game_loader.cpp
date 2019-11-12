#include "game_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // stb_image can only be included in cpp instead of header.

#include "../src/engine/audio/AudioEngine.h"
#include "../engine/BOEngine.h"
#include "../../Settings.h"
#include "../engine/input/GameInput.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "components/RaceGameComponent.h"

// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void updateListener(Vector3f pos, Vector3f rot);
void calculateSpeed(float deltaTime);
void accelSound(GameObject* player);

// camera
Camera* camera;
AudioEngine audio;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//listener
Vector3 position{ 0,0,0 };
Vector3 rotation{ 0,0,0 };
Vector3 up{ 0,0,0 };
Vector3 vel{ 0,0,0 };

// Music Toggle

bool MusicToggle;
int MusicSlider;

bool show_demo_window = true;
bool show_another_window = false;
bool show_GameMenu_window = true;//
bool show_HighScore_window = false;
bool stopgame = true;
bool gamewin = false;
bool gamelost = false;
bool isPressing = false;
int stopcase = 0;
bool showmouse = true;
int mousecase = 0;
float speed = 0;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool again = false;



GameLoader::GameLoader()
{
}

/*bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
	int id1 = colObj0Wrap->getCollisionObject()->getUserIndex();
	int id2 = colObj1Wrap->getCollisionObject()->getUserIndex();
	if ((id1 == 0 && id2 == 1) || (id1 == 1 && id2 == 0)) {
		cout << "collision" << endl;
	}
	else {
		cout << "no collision" << endl;
	}
	return false;
}*/

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

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
	//int id1 = colObj0Wrap->getUserIndex();
	//int id2 = colObj1Wrap->getUserIndex();
	RigidBodyComponent* rbc0 = static_cast<RigidBodyComponent*>(colObj0Wrap->getUserPointer());
	RigidBodyComponent* rbc1 = static_cast<RigidBodyComponent*>(colObj1Wrap->getUserPointer());
	rbc0->isHit(rbc1);
	rbc1->isHit(rbc0);
	/*if ((id1 == 0 && id2 == 1) || (id1 == 1 && id2 == 0)) { // id of the car is 0 and id of the walls is 1
		cout << "collision" << endl;
	}*/

	return false;
}

void GameLoader::createGame() {

	std::cout << "createGame" << std::endl;

	//gContactAddedCallback = callbackFunc;
	gContactProcessedCallback = callbackFunc;
	//audio.PlaySounds("game/assets/sounds/test.wav", Vector3{ 0, 0, -10 }, audio.VolumeTodB(1.0f));
	//test gun sound on the right
	//audio.PlaySounds("game/assets/sounds/gun.wav", Vector3{ 3, 0, 0}, audio.VolumeTodB(1.0f));
	//test siren sounds on the left
	//audio.PlaySounds("game/assets/sounds/siren.wav", Vector3{ -3, 0, 0}, audio.VolumeTodB(1.0f));
	//test bomb sounds center
	//audio.PlaySounds("game/assets/sounds/bomb.wav", Vector3{ 0, 0, 0}, audio.VolumeTodB(1.0f));

}

void renderPlane(btRigidBody* plane)
{
	glColor3f(0.8, 0.8, 0.8);
	btTransform t;
	plane->getMotionState()->getWorldTransform(t);
	float mat[16];
	t.getOpenGLMatrix(mat);
	glPushMatrix();
	glMultMatrixf(mat);	//translation,rotation
	glBegin(GL_QUADS);
	glVertex3f(-1000, -3, 1000);
	glVertex3f(-1000, -3, -1000);
	glVertex3f(1000, -3, -1000);
	glVertex3f(1000, -3, 1000);
	glEnd();
	glPopMatrix();
}
int BOEngine::gwidth;
int BOEngine::gHeight;

void GameLoader::startGame() {
	std::cout << "startGame" << std::endl;
	// glfw window creation
	// --------------------
	GLFWwindow* window = engine->window;
	camera = &engine->camera;

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



		GameObject* playerCar = engine->gameWorld->getGameObjectById("PlayerCar");
		if (playerCar) {
			glm::vec3 rot = playerCar->transform.rotation.getGlmVec3();
			glm::vec3 pos = playerCar->transform.position.getGlmVec3() + glm::vec3(0.0f, 1.15f, 0.0f); // look a few upper
			engine->tpCamera.update(deltaTime, playerCar->transform.position.getGlmVec3(), rot);
		}


		engine->updateEngine(deltaTime);
		calculateSpeed(-deltaTime);
		accelSound(playerCar);
		updateListener(playerCar->transform.position, playerCar->transform.rotation);
		audio.Set3dListenerAndOrientation(position, { 0 }, rotation, { 0 });

		if (playerCar) {
			racePercentage = playerCar->getComponent<RaceGameComponent>()->GetPercentage();
			if (lastRacePercentage != racePercentage)
			{
				printf("Game finished %f percent \n", racePercentage * 100.0f);
				lastRacePercentage = racePercentage;
			}
		}

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

		BOEngine boe;
		int windowW = boe.gwidth;
		int windowH = boe.gHeight;

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

		int time;
		if (show_GameMenu_window == false && show_HighScore_window == false) {


			time = int(glfwGetTime());
			if (time <= 6) {

				//CalcTextSize
				ImVec2 timeW = ImGui::CalcTextSize("The game starts in % .d second", NULL, true);
				ImVec2 firetW = ImGui::CalcTextSize("Hi BIG Onion", NULL, true);
				ImVec2 secondW = ImGui::CalcTextSize("Are you ready for tonight's game?", NULL, true);
				ImVec2 thirdW = ImGui::CalcTextSize("Let's GO.", NULL, true);

				ImGui::SetCursorPos(ImVec2((windowW / 2) - (timeW.x / 2), 200.0f));
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "The game starts in %.d second", 7 - time);

				switch (time) {
				case 1:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (firetW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Hi BIG Onion");
					break;
				case 2:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (firetW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Hi BIG Onion");
					break;
				case 3:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (secondW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Are you ready for tonight's game?");
					break;
				case 4:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (secondW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Are you ready for tonight's game?");
					break;
				case 5:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (thirdW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Let's GO.");
					break;
				case 6:
					ImGui::SetCursorPos(ImVec2((windowW / 2) - (thirdW.x / 2), 300.0f));
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Let's GO.");
					break;

				}

			}
			if (time>6) {
				stopgame = false;
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

		int speed1 = 100;

		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Speed:%d km/h", (int)speed);
		ImGui::End();

		//***************HUD: stop game***************

		ImGui::SetNextWindowSize(ImVec2(200, 80));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::StyleColorsLight();
		ImGui::Begin("Stop", 0, flags);

		if (ImGui::Button("Stop", ImVec2(200.0f, 60.0f))) // press stop to stop player movement
		{
			switch (stopcase) {
			case 0:
				stopgame = true;
				stopcase = 1;
				break;
			case 1:
				stopgame = false;
				stopcase = 0;
				break;
			}
		}
		ImGui::End();

		//*************HUD: Back Game Menu*****************

		ImGui::SetNextWindowSize(ImVec2(200, 80));
		ImGui::SetNextWindowPos(ImVec2(windowW - 200, 0));
		ImGui::Begin("menu", 0, flags);
		ImGui::StyleColorsLight();

		if (ImGui::Button("Menu", ImVec2(200.0f, 60.0f)))
		{
			show_GameMenu_window = true;
		}


		ImGui::End();

		//***************Game Main Menu****************

		if (show_GameMenu_window)
		{

			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("Big Onion", &show_GameMenu_window, flags);

			ImGui::SetCursorPos(ImVec2((windowW / 1)- (windowW / 1.85), 200.0f));
			ImGui::Text("Big Onion", ImVec2(windowW / 2, 50.0f));

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 300.0f));
			//if (ImGui::Button("Play Game", ImVec2(-1.0f, 0.0f)))
			if (ImGui::Button("Play Game", ImVec2(windowW / 2, 50.0f))) {
				show_GameMenu_window = false;
			}

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 400.0f));
			ImGui::Button("Load Game", ImVec2(windowW / 2, 50.0f));

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 500.0f));
			if (ImGui::Button("High Score", ImVec2(windowW / 2, 50.0f)))

			{
				show_GameMenu_window = false;
				show_HighScore_window = true;
			}
			
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 20), 600.0f));
			ImGui::Checkbox("Music Toggle", &MusicToggle);

			ImGui::SetCursorPos(ImVec2((windowW / 6), 650.0f));
			ImGui::SliderInt("Volume", &MusicSlider,1,5);

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
		
		if (racePercentage * 100.0f >= 100 && !again) {
			gamewin = true;
		}
		if (gamewin)
		{
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
				reload();
				again = true;
				gamewin = false;
				
			}
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 300.0f));
			if (ImGui::Button("Back Menu", ImVec2(windowW / 2, 50.0f))) {
				gamewin = false;
				show_GameMenu_window = true;
			}
			
			ImGui::End();
		}

		//***********lost window******************
		if (gamelost)
		{
			ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::StyleColorsDark();
			ImGui::Begin("lost", &gamelost, flags);

			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 100.0f));
			if (ImGui::Button("Restar Game", ImVec2(windowW / 2, 50.0f))) {
				gamelost = false;
			}
			ImGui::SetCursorPos(ImVec2((windowW / 2) - (windowW / 4), 200.0f));
			if (ImGui::Button("Back Menu", ImVec2(windowW / 2, 50.0f))) {
				gamelost = false;
				show_GameMenu_window = true;
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

//Update Listener Position and Orientation
void updateListener(Vector3f pos, Vector3f rot)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
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
			speed = speed + deltaTime * 40;
		}
		else if (speed < 100)
		{
			speed = speed + deltaTime * 80;
		}
		else if (speed < 150)
		{
			speed = speed + deltaTime * 100;
		}
		else if (speed < 201)
		{
			speed = speed + deltaTime * 120;
		}
	}
}

void accelSound(GameObject* player)
{
	if (speed >= 0)
	{
		player->getComponent<AudioPlayerComponent>()->setSpeed(speed);
		//printf("Speed: %f\n", speed);
	}
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GameLoader::processInput(GLFWwindow* window)
{
	// clear last gameinput state
	GameInput::clearState();
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

				break;
			case UB_MOVE_LEFT:
				//camera->ProcessKeyboard(LEFT, deltaTime);
				GameInput::setHorizontalAxis(1.0);
				break;
			case UB_MOVE_RIGHT:
				//camera->ProcessKeyboard(RIGHT, deltaTime);
				GameInput::setHorizontalAxis(-1.0);
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

	std::cout << "reload" << std::endl;
}

void GameLoader::exitGame() {

	std::cout << "exitGame" << std::endl;
}