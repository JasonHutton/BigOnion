#pragma once

#include "../../engine/ECS/Component.h"
#include <chrono>

class TestComponent : public Component
{
public:
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
	TestComponent();
	~TestComponent();
	void fixedUpdate(float deltaTime) override;
	std::string getComponentTypeIdentifier() override { return "Test"; }
};
