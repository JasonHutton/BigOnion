#pragma once

#include "../utils/vector3.h"

namespace GameInput
{
	namespace
	{
		float vertical;
		float horizontal;
	}

	Vector3f getAxes();

	void setVerticalAxis(float vertical);
	void setHorizontalAxis(float horizontal);
	void clearState();
};
