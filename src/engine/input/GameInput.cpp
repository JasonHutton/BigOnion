#include "GameInput.h"

Vector3f GameInput::getAxes()
{
	return Vector3f(horizontal, 0, vertical);
}

void GameInput::setHorizontalAxis(float horizontal)
{
	GameInput::horizontal = horizontal;
}

void GameInput::setVerticalAxis(float vertical)
{
	GameInput::vertical = vertical;
}

void GameInput::clearState()
{
	horizontal = vertical = 0;
}
