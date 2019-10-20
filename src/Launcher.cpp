#include <memory>
#include "game/game_loader.h"
#include "engine/BOEngine.h"

#define STB_IMAGE_IMPLEMENTATION


int runMain()
{
	std::unique_ptr<BOEngine> engine;
	try {
		std::unique_ptr<GameLoader> loader = std::make_unique<GameLoader>();

		engine = std::make_unique<BOEngine>();
		
		std::cout << "Initializing Virtual File System..." << std::endl;
		FileSystem::Init("./src");

		loader->createGame();
		engine->initialize();

		loader->setEngine(*engine);
		loader->startGame();

		return engine->exit();
	}
	catch (std::exception& e) {
		if (engine) {
			engine->exitInError(e.what());
		}
		else {
			std::cout << "Exception initialising core: " << e.what() << std::endl;
		}
		return 1;
	}
	catch (...) {
		if (engine) {
			engine->exitInError("");
		}
		else {
			std::cout << "Unknown exception initialising core." << std::endl;
		}
		return 1;
	}
}

int main()
{
	return runMain();
}

