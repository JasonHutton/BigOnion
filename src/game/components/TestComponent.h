#pragma once

#include "../../engine/ECS/Component.h"

class TestComponent : public Component
{
public:
	~TestComponent();
	void update(float deltaTime) override;
};
