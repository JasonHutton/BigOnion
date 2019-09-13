#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../engine/graphic/shader_m.h"
#include "../engine/graphic/camera.h"
#include "../engine/graphic/model.h"

#include <iostream>


class BOEngine
{
	public: 
		GLFWwindow* window;
		Camera camera;

		const unsigned int SCR_WIDTH = 1000;
		const unsigned int SCR_HEIGHT = 800;

		BOEngine();

		void initialize();
		void preRender();
		void updateEngine(float deltaTime);
		void render();



};

