#pragma once
#include "include/bullet/LinearMath/btIDebugDraw.h"
class DebugDraw :
	public btIDebugDraw
{
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
};

