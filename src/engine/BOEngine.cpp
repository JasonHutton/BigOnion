#include "BOEngine.h"
#include "ECS/GameObject.h"
#include "../game/components/TestComponent.h"
#include "../game/GameWorldHelper.h"


BOEngine::BOEngine()
{
}

/*
	Initializes the OpenGL context and some important local variables.
*/
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

	// Shader loading
	// TODO: some models may want different shaders. cross that bridge when we meet it
	modelShader = new Shader("engine/graphic/shader/model_loading.vs", "engine/graphic/shader/model_loading.fs");

	// Game World initialization
	currentTime = std::chrono::high_resolution_clock::now();

	GameWorldHelper::initTestScene(this, modelShader);
}

void BOEngine::preRender()
{
	glEnable(GL_DEPTH_TEST);
	//TODO comment: shader test
	Shader ourShader("engine/graphic/shader/vertex.glsl", "engine/graphic/shader/fragment.glsl"); // you can name your shader files however you like
	Shader lightShader("engine/graphic/shader/vertex.glsl", "engine/graphic/shader/light.fs.glsl");



}

/*
	Propogates updates to the GameWorld, and renders.
*/
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
		gameWorld->fixedUpdateGameObjects(FIXED_DELTA_TIME);
		accumulator -= FIXED_DELTA_TIME_DURATION;
	}

	// this value is currently unused. it could be useful in the future for interpolating between fixed game states on higher framerates
	// double alpha = accumulator / FIXED_DELTA_TIME_DURATION;
	gameWorld->updateGameObjects(deltaTime);

	render();
}

/*
	Calculates view transformation, and renders all models in the scene.
*/
void BOEngine::render()
{
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int scrWidth = 10; //TODO get from window
	int scrHeight = 8; //TODO get from window

	glfwGetWindowSize(window, &scrWidth, &scrHeight);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();

	// don't forget to enable shader before setting uniforms
	modelShader->use();

	modelShader->setMat4("projection", projection);
	modelShader->setMat4("view", view);

	for (RenderComponent* rc : renderComponents)
	{
		rc->model.Draw();
	}
}

/*
	Adds a RenderComponent to the scene.
*/
void BOEngine::addRenderComponent(RenderComponent* renderComponent)
{
	renderComponents.push_back(renderComponent);
}

void BOEngine::exitInError(const std::string& error)
{
	std::cout << "\n\nUnknown unhandled exception. " << error << std::endl;
}
