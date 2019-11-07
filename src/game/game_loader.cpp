#include "game_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // stb_image can only be included in cpp instead of header.

#include "../src/engine/audio/AudioEngine.h"
#include "../engine/BOEngine.h"
#include "../../Settings.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"



// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void updateListener();

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
Vector3 front{ 0,0,0 };
Vector3 up{ 0,0,0 };
Vector3 vel{ 0,0,0 };

bool show_demo_window = true;
bool show_another_window = false;
bool show_GameMenu_window = true;
bool show_HighScore_window = false;
bool stopgame = false;
int stopcase = 0;
bool showmouse = true;
int mousecase = 0;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

BOEngine BOE;

GameLoader::GameLoader()
{
}

void GameLoader::createGame() {

	std::cout << "createGame" << std::endl;

	
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

		engine->updateEngine(deltaTime);

		updateListener();
		audio.Set3dListenerAndOrientation(position, vel, up, front);
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

		//new Imgui frame
		ImGui_ImplGlfwGL3_NewFrame();
		
		//ImGuiWindowFlags flags = ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
		//ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;//no title bar and fixed window size

		//************HUD: Score*********************
		ImGui::SetNextWindowSize(ImVec2(200, 100));        //window size
		ImGui::SetNextWindowPos(ImVec2(0, 700));     //window position
		ImGui::Begin("Score",0,flags);

		int score1 = 100;	
		
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Score: %.d",score1 );
		//ImGui::StyleColorsDark();
		ImGui::End();

		//***************HUD: Speed******************

		ImGui::SetNextWindowSize(ImVec2(200, 100));        
		ImGui::SetNextWindowPos(ImVec2(800, 700));             
		ImGui::Begin("Speed",0, flags);
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

		int speed1 = 100;
		
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Speed:%.d",speed1);
		ImGui::End();

		//***************HUD: stop game***************

		ImGui::SetNextWindowSize(ImVec2(200, 80));        
		ImGui::SetNextWindowPos(ImVec2(0,0));             
		ImGui::Begin("Stop", 0, flags);

		if (ImGui::Button("Stop", ImVec2(200.0f, 60.0f))) //stop player movement
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

		//*************Back Game Menu*****************

		ImGui::SetNextWindowSize(ImVec2(200, 80));       
		ImGui::SetNextWindowPos(ImVec2(800, 0));            
		ImGui::Begin("menu", 0, flags);

			if (ImGui::Button("Menu", ImVec2(200.0f, 60.0f)))
			{
				show_GameMenu_window = true;
			}

		ImGui::End();

		//***************Game Main Menu****************
		
		if (show_GameMenu_window)
		{
			ImGui::SetNextWindowSize(ImVec2(1000, 800));       
			ImGui::SetNextWindowPos(ImVec2(0, 0));             
			ImGui::StyleColorsDark();
			ImGui::Begin("Big Onion", &show_GameMenu_window, flags);
	
			ImGui::SetCursorPos(ImVec2(250.0f, 100.0f));
			//if (ImGui::Button("Play Game", ImVec2(-1.0f, 0.0f)))
			if (ImGui::Button("Play Game", ImVec2(500.0f, 50.0f))) {
				show_GameMenu_window = false;
			 }

			ImGui::SetCursorPos(ImVec2(250.0f, 200.0f));
			ImGui::Button("Load Game", ImVec2(500.0f, 50.0f));

			ImGui::SetCursorPos(ImVec2(250.0f, 300.0f));
			if (ImGui::Button("High Score", ImVec2(500.0f, 50.0f)))
			{
				show_GameMenu_window = false;
				show_HighScore_window = true;
			}

			ImGui::SetCursorPos(ImVec2(250.0f, 400.0f));
			if (ImGui::Button("Exit", ImVec2(500.0f, 50.0f))) 
				break;	

			ImGui::End();	

		}
		//**********High score list Window************
		static const char* scores[]{ "1","2","3","4","5","6","7","8","9","10" };//high score list
		static int selectscore = 0;

		if (show_HighScore_window)
		{
			ImGui::SetNextWindowSize(ImVec2(1000, 800));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::Begin("Big Onion", &show_HighScore_window, flags);
			ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
			if (ImGui::Button("Back", ImVec2(200.0f, 60.0f)))
			{
				show_HighScore_window = false;
				show_GameMenu_window = true;
			}
			ImGui::End();
			
			ImGui::SetNextWindowSize(ImVec2(500, 400));
			ImGui::SetNextWindowPos(ImVec2(180, 200));
			ImGui::Begin("Big Onion", &show_HighScore_window, flags);
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "                                         High Score");
			ImGui::ListBox("", &selectscore, scores, IM_ARRAYSIZE(scores));
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
void updateListener()
{
		position.x = camera->Position.x;
		position.y = camera->Position.y;
		position.z = camera->Position.z;
		front.x = camera->Front.x;
		front.y = camera->Front.y;
		front.z = camera->Front.z;
		up.x = camera->Up.x;
		up.y = camera->Up.y;
		up.z = camera->Up.z;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GameLoader::processInput(GLFWwindow* window)
{
	// Check all bound controls
	for (map<int, keyState>::iterator it = input.GetAllKeyStates().begin(); it != input.GetAllKeyStates().end(); it++)
	{
		// If the bound control is being pressed....
		if (glfwGetKey(window, it->first) == GLFW_PRESS)
		{
			// See if a bound control has a User Button associated with it.
			ContextControl cc = input.GetControl(it->first);
			// Do what the context control->User Button says to do.
			switch(cc.GetControl("")) // Default context.
			{
			case UB_FORCE_QUIT:
				glfwSetWindowShouldClose(window, true);
				break;
			case UB_MOVE_FORWARD:
				camera->ProcessKeyboard(FORWARD, deltaTime);
				break;
			case UB_MOVE_BACKWARD:
				camera->ProcessKeyboard(BACKWARD, deltaTime);
				break;
			case UB_MOVE_LEFT:
				camera->ProcessKeyboard(LEFT, deltaTime);
				break;
			case UB_MOVE_RIGHT:
				camera->ProcessKeyboard(RIGHT, deltaTime);
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