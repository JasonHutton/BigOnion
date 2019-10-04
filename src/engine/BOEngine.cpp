#include "BOEngine.h"
#include "ECS/GameObject.h"
#include "../game/components/TestComponent.h"



//// settings

//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


BOEngine::BOEngine(std::unique_ptr<Game> gm)
{
	game = std::move(gm);
}

void BOEngine::initialize()
{
	std::cout << "BOEngine::initialize" << std::endl;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Big Onion", NULL, NULL);
	this->camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		// return -1;
	}

	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	// Game World initialization
	currentTime = std::chrono::high_resolution_clock::now();
	gameWorld = GameWorld();
	// commented out for the sanity of my groupmates :)
	/*
	GameObject* obj = new GameObject("Test");
	obj->addComponent(new TestComponent());
	gameWorld.addGameObject(obj);
	*/

	game->init(this);
}

void BOEngine::preRender()
{
	glEnable(GL_DEPTH_TEST);
	//TODO comment: shader test
	Shader ourShader("src/engine/graphic/shader/vertex.glsl", "src/engine/graphic/shader/fragment.glsl"); // you can name your shader files however you like
	Shader lightShader("src/engine/graphic/shader/vertex.glsl", "src/engine/graphic/shader/light.fs.glsl");



}

void BOEngine::updateEngine(float deltaTime)
{
	// figure out how much time has elapsed since the last frame, capping at the min fps frametime
	auto newTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> frameTime = newTime - currentTime;
	if (frameTime > MAX_FRAMETIME)
	{
		frameTime = MAX_FRAMETIME;
	}
	currentTime = newTime;

	// add the frametime to the accumulator
	accumulator += frameTime;
	// do fixed updates until the accumulator is near empty
	while (accumulator >= FIXED_DELTA_TIME_DURATION)
	{
		gameWorld.fixedUpdateGameObjects(FIXED_DELTA_TIME);
		accumulator -= FIXED_DELTA_TIME_DURATION;
	}

	// this value is currently unused. it could be useful in the future for interpolating between fixed game states on higher framerates
	// double alpha = accumulator / FIXED_DELTA_TIME_DURATION;
	gameWorld.updateGameObjects(deltaTime);


	game->updateWithDelta(deltaTime);

	game->render(this);
}

void BOEngine::exitInError(const std::string& error)
{
	std::cout << "\n\nUnknown unhandled exception." << error << std::endl;
}
