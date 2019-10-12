#pragma once

#include "../engine/BOEngine.fwd.h"
#include "../engine/graphic/shader_m.h"

class BOEngine;

class GameWorldHelper
{
public:
	static void initTestScene(BOEngine* engine, Shader* shader);
private:
	GameWorldHelper();
};
