#include "GameInput.h"

Vector3f GameInput::getAxes()
{
	return Vector3f(forward, turn, forward);
}

void GameInput::setForwardAxis(float forward)
{
	GameInput::forward = forward;
}

void GameInput::setTurningAxis(float turn)
{
	GameInput::turn = turn;
}

void GameInput::clearState()
{
	forward = turn = 0;
}
