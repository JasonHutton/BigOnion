#pragma once

#include "../engine/BOEngine.h"
#include "../src/engine/audio/AudioEngine.h"
#include "../FileSystem.h"
#include "../InputHandler.h"

class GameLoader
{
	private:
		BOEngine* engine = nullptr;

		void processInput(GLFWwindow* window);

	public:
		GameLoader();
		AudioEngine audio;
		InputHandler input;

		void createGame();
		void setEngine(BOEngine&);
		void reload();
		void startGame();
		void exitGame();
};
