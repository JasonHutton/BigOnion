#pragma once
#include "../ECS/Component.h"
#include "../ECS/GameObject.h"
#include "ShaderAttribute.h"
#include "../utils/Vector3.h"


class RenderComponent 
	: public Component
{
public:
	RenderComponent(ShaderAttribute* _shaderAttribute) :shaderAttribute(_shaderAttribute) {};
	void lateUpdate(float deltaTime) override;

private:
	ShaderAttribute* shaderAttribute;

};

