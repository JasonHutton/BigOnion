#include "game_renderer.h"


GameRenderer::GameRenderer()
{
}

void GameRenderer::init()
{
	modelShader = Shader("src/engine/graphic/shader/model_loading.vs", "src/engine/graphic/shader/model_loading.fs");
	ourModel = Model("src/game/assets/nanosuit/nanosuit.obj");
}

void GameRenderer::updateWithDelta(float deltaTime)
{
}

void GameRenderer::render(BOEngine* engine)
{
	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	modelShader.use();

	int scrWidth = 10; //TODO get from window
	int scrHeight = 8; //TODO get from window

	glfwGetWindowSize(engine->window, &scrWidth, &scrHeight);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(engine->camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = engine->camera.GetViewMatrix();
	
	modelShader.setMat4("projection", projection);
	modelShader.setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	modelShader.setMat4("model", model);
	ourModel.Draw(modelShader);


}
