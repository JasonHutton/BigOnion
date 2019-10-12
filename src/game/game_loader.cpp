#include "game_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // stb_image can only be included in cpp instead of header.


#include "../engine/BOEngine.h"

#include "../SoundFile.h"

// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void updateListener();

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera* camera;
double lastX = SCR_WIDTH / 2.0f;
double lastY = SCR_HEIGHT / 2.0f;
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

GameLoader::GameLoader()
{
}

void GameLoader::createGame() {

	std::cout << "createGame" << std::endl;
	FileSystem::Init("./src");
	audio.Init();
	
	audio.PlaySounds("game/assets/sounds/test.wav", Vector3{ 0, 0, -10 }, audio.VolumeTodB(1.0f));
	//test gun sound on the right
	audio.PlaySounds("game/assets/sounds/gun.wav", Vector3{ 3, 0, 0}, audio.VolumeTodB(1.0f));
	//test siren sounds on the left
	audio.PlaySounds("game/assets/sounds/siren.wav", Vector3{ -3, 0, 0}, audio.VolumeTodB(1.0f));
	//test bomb sounds center
	audio.PlaySounds("game/assets/sounds/bomb.wav", Vector3{ 0, 0, 0}, audio.VolumeTodB(1.0f));

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
		processInput(window);
		
		engine->updateEngine(deltaTime);

		updateListener();
		audio.Set3dListenerAndOrientation(position, vel, up, front);
		audio.Update();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
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
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
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
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

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