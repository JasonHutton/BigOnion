#pragma once
#include "../ECS/Component.h"
#include "model.h"
#include "../BOEngine.fwd.h"


class RenderComponent 
	: public Component
{
public:
	Model model;
	RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader);
	void lateUpdate(float deltaTime) override;

};

