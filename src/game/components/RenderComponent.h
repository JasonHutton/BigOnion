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
	bool isSelfRotation = false; // rotate axis, world is defualt,

	RenderComponent(BOEngine* engine, std::string modelPath, Shader* shader);
	~RenderComponent();
	void update(float deltaTime) override;
	std::string componentTypeID() override { return typeID; }
	glm::mat4 toModelMatrix();
private:
	BOEngine* engine;

};

