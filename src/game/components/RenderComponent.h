#pragma once
#include "../../engine/ECS/Component.h"
#include "../../engine/graphic/model.h"
#include "../../engine/BOEngine.fwd.h"


class RenderComponent 
	: public Component
{
public:
	static const std::string typeID;
	Model model;
	RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader);
	void update(float deltaTime) override;
	std::string componentTypeID() override { return typeID; }

};

