#pragma once

#include "../engine/BOEngine.h"
#include "game.h"
#include "../src/engine/audio/AudioEngine.h"

class GameLoader
{
	private:
		BOEngine* engine = nullptr;

	public:
		GameLoader();
		AudioEngine audio;

		std::unique_ptr<Game> createGame();
		void setEngine(BOEngine&);
		void reload();
		void startGame();
		void exitGame();
};

