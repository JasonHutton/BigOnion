#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "shader.h"

enum AttributeType
{
	UNIFORM_BOOL,
	UNIFORM_INT,
	UNIFORM_FLOAT,
	UNIFORM_VECTOR2,
	UNIFORM_VECTOR3,
	UNIFORM_VECTOR4,
	UNIFORM_MATRIX2,
	UNIFORM_MATRIX3,
	UNIFORM_MATRIX4,
};

struct ShaderAttributeValue
{
	std::string name;
	AttributeType type;
	bool valueb;
	int valuei;
	float valuef;
	float x;
	float y;
	float z;
	float w;
	glm::mat2  valueM2f;
	glm::mat3  valueM3f;
	glm::mat4  valueM4f;

	ShaderAttributeValue(std::string _name, AttributeType _type) : name(_name), type(_type) {};
};


class ShaderAttribute
{

public:
	std::vector<ShaderAttributeValue> attributeValues;

	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_BOOL);
		shaderValue.valueb = value;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_INT);
		shaderValue.valuei = value;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_FLOAT);
		shaderValue.valuef = value;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR2);
		shaderValue.x = value.x;
		shaderValue.y = value.y;
		attributeValues.push_back(shaderValue);
	}
	void setVec2(const std::string& name, float x, float y)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR2);
		shaderValue.x = x;
		shaderValue.y = y;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR3);
		shaderValue.x = value.x;
		shaderValue.y = value.y;
		shaderValue.z = value.z;
		attributeValues.push_back(shaderValue);
	}
	void setVec3(const std::string& name, float x, float y, float z)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR3);
		shaderValue.x = x;
		shaderValue.y = y;
		shaderValue.z = z;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR4);
		shaderValue.x = value.x;
		shaderValue.y = value.y;
		shaderValue.z = value.z;
		shaderValue.w = value.w;
		attributeValues.push_back(shaderValue);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_VECTOR4);
		shaderValue.x = x;
		shaderValue.y = y;
		shaderValue.z = z;
		shaderValue.w = w;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_MATRIX2);
		shaderValue.valueM2f = mat;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_MATRIX3);
		shaderValue.valueM3f = mat;
		attributeValues.push_back(shaderValue);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat)
	{
		ShaderAttributeValue shaderValue(name, UNIFORM_MATRIX4);
		shaderValue.valueM4f = mat;
		attributeValues.push_back(shaderValue);
	}

	void applyAttributeTo(Shader* shader) {

		for (ShaderAttributeValue value : attributeValues) {
			switch (value.type)
			{
			case UNIFORM_BOOL:
				shader->setBool(value.name, value.valueb);
				break;
			case UNIFORM_INT:
				shader->setInt(value.name, value.valuei);
				break;
			case UNIFORM_FLOAT:
				shader->setFloat(value.name, value.valuef);
				break;
			case UNIFORM_VECTOR2:
				shader->setVec2(value.name, value.x, value.y);
				break;
			case UNIFORM_VECTOR3:
				shader->setVec3(value.name, value.x, value.y, value.z);
				break;
			case UNIFORM_VECTOR4:
				shader->setVec4(value.name, value.x, value.y, value.z, value.w);
				break;
			case UNIFORM_MATRIX2:
				shader->setMat2(value.name, value.valueM2f);
				break;
			case UNIFORM_MATRIX3:
				shader->setMat3(value.name, value.valueM3f);
				break;
			case UNIFORM_MATRIX4:
				shader->setMat4(value.name, value.valueM4f);
				break;
			default:
				std::cout << "ERROR: unknown ShaderAttributeValue Type" << std::endl;
				break;
			}
		}
		attributeValues.clear();
	}

	ShaderAttribute();
};

