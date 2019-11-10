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
#include "graphic/ThirdPersonCamera.h"
#include "../game/components/RenderComponent.h"
#include "../src/engine/audio/AudioEngine.h"
#include "../game/components/AudioPlayerComponent.h"

#include "ECS/GameWorld.h"
#include "../game/components/RigidbodyComponent.h"

#include <iostream>

class BOEngine
{

public: 
	GLFWwindow* window;
	Camera camera; // free camera
	ThirdPersonCamera tpCamera;
	GameWorld* gameWorld = nullptr;
	AudioEngine audio;

	BOEngine();

	void initialize();
	void preRender();
	void updateEngine(float deltaTime);
	void render();
	void addRenderComponent(RenderComponent* renderComponent);

	void exitInError(const std::string& error);
	int exit() const { return exitCode; }
	
	static int gwidth;
	static int gHeight;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	std::chrono::duration<double> accumulator;
	
	int exitCode;
	

	std::vector<RenderComponent*> renderComponents;
};
