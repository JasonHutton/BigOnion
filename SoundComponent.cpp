#include "SoundComponent.h"
#include "src/engine/ECS/GameObject.h"
#include "src/engine/ECS/GameWorld.h"

const std::string AudioComponent::typeID = "Audio";

AudioComponent::AudioPlayerComponent(AudioEngine* sound)
	: audio(sound)
{
}

void AudioPlayerComponent::update(float deltaTime)
{
	
}