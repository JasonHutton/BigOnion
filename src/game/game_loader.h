#pragma once

#include "../engine/BOEngine.h"
#include "game_renderer.h"
#include "game_controller.h"

class GameLoader
{
	private:
		BOEngine engine;
		GameRenderer gameRenderer;
		void setupGame();
	public:
		GameLoader();

		void createGame();
		void reload();
		void startGame();
		void exitGame();
};

