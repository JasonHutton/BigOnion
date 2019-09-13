#pragma once

#include "../engine/BOEngine.h"

class GameRenderer
{
public:
	BOEngine engine;

	GameRenderer();

	void init();

	void updateWithDelta(float deltaTime);

	void render(BOEngine engine);

private:
	//TODO: move object to game
	Shader modelShader;
	Model ourModel;
};

