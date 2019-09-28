#include "TestComponent.h"
#include <iostream>

TestComponent::~TestComponent()
{
	std::cout << "Test component properly deconstructed." << std::endl;
}

void TestComponent::update(float deltaTime)
{
	std::cout << "This is a test component update! deltaTime: " << deltaTime << std::endl;
}
