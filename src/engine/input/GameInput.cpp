#include "GameInput.h"

Vector3f GameInput::getAxes()
{
	return Vector3f(vertical, horizontal, 0);
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
	vertical = horizontal = 0;
}
