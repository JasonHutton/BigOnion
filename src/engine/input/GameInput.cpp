#include "GameInput.h"

float GameInput::getVerticalAxis()
{
	return GameInput::vertical;
}

float GameInput::getHorizontalAxis()
{
	return GameInput::horizontal;
}

void GameInput::setVerticalAxis(float vertical)
{
	GameInput::vertical = vertical;
}

void GameInput::setHorizontalAxis(float horizontal)
{
	GameInput::horizontal = horizontal;
}

void GameInput::clearState()
{
	GameInput::vertical = GameInput::horizontal = 0;
}
