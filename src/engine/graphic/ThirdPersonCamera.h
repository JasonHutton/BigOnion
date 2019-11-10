#pragma once

#include "../utils/Vector3.h"

#include <glm/gtc/matrix_transform.hpp>
class ThirdPersonCamera
{
public:
	float cameraDistance = 8.0f;
	float cameraHeight = 1.3f;
	float pitch = glm::radians(90.0f);
	float rotateSpeed = glm::radians(50.0f); // 50 degress per second

	ThirdPersonCamera();
	~ThirdPersonCamera();

	void lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);

	// delay rotate to position
	void rotate(glm::vec3 targetRotation);
	void update(float deltaTime, const glm::vec3& targetPosition, glm::vec3 m_targetRotation);

	glm::mat4 GetViewMatrix();
	glm::vec3 GetPosition();

private:
	static const float DEFAULT_FOVX;
	static const float DEFAULT_ZFAR;
	static const float DEFAULT_ZNEAR;
	static const glm::vec3 WORLD_XAXIS;
	static const glm::vec3 WORLD_YAXIS;
	static const glm::vec3 WORLD_ZAXIS;

	glm::mat4 m_viewMatrix;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_targetRotation;
	float lastEulerAngleY = 0;
};
