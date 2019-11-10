#include "ThirdPersonCamera.h"
#include <algorithm>

const glm::vec3 ThirdPersonCamera::WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const glm::vec3 ThirdPersonCamera::WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const glm::vec3 ThirdPersonCamera::WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

ThirdPersonCamera::ThirdPersonCamera()
{
	m_viewMatrix = glm::mat4(1.0f);
	m_cameraPosition = glm::vec3(0.0f, cameraHeight, 0.0f);
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

glm::vec3 ThirdPersonCamera::GetPosition() {
	return m_cameraPosition;
}

glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	return m_viewMatrix;
}

void ThirdPersonCamera::lookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_viewMatrix = glm::lookAt(eye, target, up);
}

void ThirdPersonCamera::rotate(glm::vec3 targetRotation)
{
	m_targetRotation = targetRotation;
}
void ThirdPersonCamera::update(float deltaTime, const glm::vec3& targetPosition, glm::vec3 targetRotation)
{

	// Determine how many degrees of rotation to apply based on current time.

	float targetEulerAngleY = targetRotation.y; // eulerAngle pitch is [0,90], [-0, -90]
	if (abs(targetRotation.x) > 1.57) // x = only 0 or 180
	{
		targetEulerAngleY = glm::radians(180.0f) - targetRotation.y;
	}

	targetEulerAngleY += pitch;

	//debug
	//glm::vec3 rt = targetRotation;
	//printf("rotation.x=%f, y: %f, z:%f fixed= %f \n", glm::degrees(rt.x), glm::degrees(rt.y), glm::degrees(rt.z), glm::degrees(fixedEulerAngleY));


	float rotateDistanceX = targetEulerAngleY - lastEulerAngleY;
	float deltaMove = (rotateSpeed + rotateDistanceX / 60) * deltaTime; // speed * time, add speed when distance is too big
	float fixedEulerAngleY = lastEulerAngleY;

	if (abs(rotateDistanceX) > deltaMove) {
		fixedEulerAngleY += std::copysign(deltaMove, rotateDistanceX);
	}
	else {
		fixedEulerAngleY = targetEulerAngleY;
	}

	m_cameraPosition.x = targetPosition.x + sin(fixedEulerAngleY) * cameraDistance;
	m_cameraPosition.y = cameraHeight;
	m_cameraPosition.z = targetPosition.z + cos(fixedEulerAngleY) * cameraDistance;

	//// Rebuild the view matrix.
	lookAt(
		m_cameraPosition,
		targetPosition,
		WORLD_YAXIS
	);

	lastEulerAngleY = fixedEulerAngleY;
}