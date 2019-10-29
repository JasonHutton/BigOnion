#pragma once
#include "../../engine/ECS/Component.h"
#include <iostream>


class TypeTestComponent
	: public Component
{
public:
	TypeTestComponent(std::string message) : message(message) {};
	void talk() { std::cout << message << std::endl; };
	std::string componentTypeID() override { return message; }

private:
	std::string message;
};
