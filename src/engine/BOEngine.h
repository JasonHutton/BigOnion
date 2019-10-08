#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#include "graphic/shader_m.h"
#include "graphic/camera.h"
#include "graphic/model.h"
#include "graphic/ShaderAttribute.h"
#include "graphic/RenderComponent.h"

#include "ECS/GameWorld.h"
#include "../game/components/RigidbodyComponent.h"

#include <iostream>

#include "../game/game.h" //TODO move to engine


class Game;

class BOEngine
{

public: 
	GLFWwindow* window;
	Camera camera;
	GameWorld gameWorld;

	const unsigned int SCR_WIDTH = 1000;
	const unsigned int SCR_HEIGHT = 800;

	BOEngine(std::unique_ptr<Game> game);

	void initialize();
	void preRender();
	void updateEngine(float deltaTime);
	void render();
	void addRenderComponent(RenderComponent* renderComponent);

	void exitInError(const std::string& error);
	int exit() const { return exitCode; }

private:
	const std::chrono::duration<double> MAX_FRAMETIME = std::chrono::duration<double>(0.25);
	const double FIXED_DELTA_TIME = 1.0 / 60.0;
	const std::chrono::duration<double> FIXED_DELTA_TIME_DURATION = std::chrono::duration<double>(FIXED_DELTA_TIME);
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	std::chrono::duration<double> accumulator;
	
	int exitCode;

	Shader* modelShader;
	std::vector<RenderComponent*> renderComponents;

	std::unique_ptr<Game> game; // delete this
};
