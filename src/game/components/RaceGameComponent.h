#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "../src/engine/ECS/Component.h"

class RaceGameComponent :
	public Component
{
public:
	std::vector<glm::vec3> checkpoints;

	static const std::string typeID;
	std::string componentTypeID() override { return typeID; }

	RaceGameComponent();

	void update(float deltaTime) override;

	void resetPercentage();
	float GetPercentage();
	// void onAddToGameWorld() override;

private:
	int reachCheckPoint = 0;
	const float passDistance = 8.0f;
};
