#pragma once

#include "../engine/BOEngine.h"
#include "game_renderer.h"
#include "game_controller.h"
#include "../src/engine/audio/AudioEngine.h"

class GameLoader
{
	private:
		BOEngine engine;
		GameRenderer gameRenderer;
		
		void setupGame();
	public:
		GameLoader();
		AudioEngine audio;
		void createGame();
		void reload();
		void startGame();
		void exitGame();
};

