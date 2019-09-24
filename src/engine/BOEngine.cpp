#include "BOEngine.h"



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


BOEngine::BOEngine()
{
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

}

void BOEngine::preRender()
{
	// configure global opengl state
// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// build and compile our shader program
	// ------------------------------------
	
	//TODO comment: shader test
	Shader ourShader("src/engine/graphic/shader/vertex.glsl", "src/engine/graphic/shader/fragment.glsl"); // you can name your shader files however you like
	Shader lightShader("src/engine/graphic/shader/vertex.glsl", "src/engine/graphic/shader/light.fs.glsl");



}

void BOEngine::updateEngine(float deltaTime)
{
	std::cout << "Test" << std::endl;
}

void BOEngine::render()
{

}

