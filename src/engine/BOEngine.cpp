#include "BOEngine.h"
#include "ECS/GameObject.h"
#include "../game/GameWorldHelper.h"
#include "../../Settings.h"

#include "imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int BOEngine::gwidth;
int BOEngine::gHeight;

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
	this->window = glfwCreateWindow(Settings::CurrentResolution.width, Settings::CurrentResolution.height, "Big Onion", NULL, NULL);
	this->camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		// return -1;
	}

	glfwMakeContextCurrent(window);

	//Imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui_ImplGlfwGL3_Init(window, true);
	ImFont* pFont = io.Fonts->AddFontFromFileTTF("engine/assets/ui/Roboto-Black.ttf", 30.0f);
	
	ImGui::PushStyleColor(ImGuiCol_WindowBg, (0, 0, 0, 0));


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	// Shader loading
	// TODO: some models may want different shaders. cross that bridge when we meet it



	// Game World initialization
	currentTime = std::chrono::high_resolution_clock::now();

	audio.Init();

	int scrWidth, scrHeight;
	glfwGetWindowSize(window, &scrWidth, &scrHeight);
	this->gwidth = scrWidth;
	this->gHeight = scrHeight;
}

void BOEngine::preRender()
{
	glEnable(GL_DEPTH_TEST);

}

/*
	Propogates updates to the GameWorld, and renders.
*/
void BOEngine::updateEngine(float deltaTime)
{
	gameWorld->updateGameObjects(deltaTime);
	audio.Update();
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



	int scrWidth, scrHeight;
	glfwGetWindowSize(window, &scrWidth, &scrHeight);
	this->gwidth = scrWidth;
	this->gHeight = scrHeight;
	
	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(ZOOM), (float)gwidth / (float)gHeight, 0.1f, 100.0f);
	glm::mat4 view = tpCamera.GetViewMatrix();

	// don't forget to enable shader before setting uniforms

	Shader* shader = NULL;

	for (RenderComponent* rc : renderComponents)
	{
		shader = rc->model.shader;
		shader->use();
		shader->setVec3("viewPos", tpCamera.GetPosition());
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);

		rc->model.Draw();
	}

	// draw skybox as last
	this->skybox.skyboxShader->use();
	view = glm::mat4(glm::mat3(tpCamera.GetViewMatrix())); // remove translation from the view matrix
	this->skybox.skyboxShader->setMat4("view", view);
	this->skybox.skyboxShader->setMat4("projection", projection);
	// skybox cube
	this->skybox.draw();
}




/*
	Adds a RenderComponent to the scene.
*/
void BOEngine::addRenderComponent(RenderComponent* renderComponent)
{
	renderComponents.push_back(renderComponent);
}

void BOEngine::removeRenderComponent(RenderComponent* renderComponent)
{
	renderComponents.erase(std::remove(renderComponents.begin(), renderComponents.end(), renderComponent), renderComponents.end());
}

void BOEngine::exitInError(const std::string& error)
{
	std::cout << "\n\nUnknown unhandled exception. " << error << std::endl;
}
