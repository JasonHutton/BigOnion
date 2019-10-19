#pragma once
#include "../../engine/ECS/Component.h"
#include "../../engine/graphic/model.h"
#include "../../engine/BOEngine.fwd.h"


class RenderComponent 
	: public Component
{
public:
	Model model;
	RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader);
	void lateUpdate(float deltaTime) override;
	std::string getComponentTypeIdentifier() override { return "Render"; }

};

