#pragma once

#include "../engine/BOEngine.h"
#include "../src/engine/audio/AudioEngine.h"
#include "../FileSystem.h"

class GameLoader
{
	private:
		BOEngine* engine = nullptr;

	public:
		GameLoader();
		AudioEngine audio;

		void createGame();
		void setEngine(BOEngine&);
		void reload();
		void startGame();
		void exitGame();
};
