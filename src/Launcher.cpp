#include "game/game_loader.h"

#define STB_IMAGE_IMPLEMENTATION

int main()
{
	GameLoader gameLoader;
	gameLoader.createGame();
	gameLoader.startGame();
}