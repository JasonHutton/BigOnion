#pragma once

#include "../utils/vector3.h"

namespace GameInput
{
	namespace
	{
		float forward;
		float turn;
	}

	Vector3f getAxes();

	void setForwardAxis(float forward);
	void setTurningAxis(float turn);
	void clearState();
};
