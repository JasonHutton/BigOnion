#include "AudioListenerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"

const std::string AudioListenerComponent::typeID = "Listener";

AudioListenerComponent::AudioListenerComponent()
{
	
}

void AudioListenerComponent::update(float deltaTime)
{
	audio.Set3dListenerAndOrientation(convert(gameObject->transform.position), Vector3{ 0 }, convert(gameObject->transform.rotation), Vector3{ 0 });
}

Vector3 AudioListenerComponent::convert(Vector3f vPos)
{
	Vector3 vector = Vector3{ vPos.x,vPos.y,vPos.z };
	return vector;
}