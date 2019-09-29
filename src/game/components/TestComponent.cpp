#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent()
{
	lastTime = std::chrono::high_resolution_clock::now();
}

TestComponent::~TestComponent()
{
	std::cout << "Test component properly deconstructed." << std::endl;
}

void TestComponent::fixedUpdate(float deltaTime)
{
	auto newTime = std::chrono::high_resolution_clock::now();
	double realDelta = (double)(std::chrono::duration_cast<std::chrono::milliseconds>(newTime - lastTime).count()) / 1000.0;
	std::cout << "Fixed deltaTime: " << deltaTime << " Real deltaTime: " << realDelta << std::endl;
	lastTime = newTime;
}
