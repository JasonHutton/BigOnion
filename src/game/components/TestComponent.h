#pragma once

#include "../../engine/ECS/Component.h"

class TestComponent : public Component
{
public:
	void update(float deltaTime) override;
};
