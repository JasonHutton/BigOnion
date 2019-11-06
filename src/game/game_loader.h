#pragma once

#include "../engine/BOEngine.h"
#include "../FileSystem.h"
#include "../engine/input/InputHandler.h"

class GameLoader
{
	private:
		BOEngine* engine = nullptr;

		void processInput(GLFWwindow* window);

	public:
		GameLoader();
		
		InputHandler input;

		void createGame();
		void setEngine(BOEngine&);
		void reload();
		void startGame();
		void exitGame();
};
