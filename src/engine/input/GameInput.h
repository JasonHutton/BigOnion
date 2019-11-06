#pragma once

#include "../utils/vector3.h"

namespace GameInput
{
	namespace
	{
		float horizontal;
		float vertical;
	}

	Vector3f getAxes();

	void setHorizontalAxis(float horizontal);
	void setVerticalAxis(float vertical);
	void clearState();
};
