#include "AudioPlayerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"

const std::string AudioPlayerComponent::typeID = "Audio";
int AudioPlayerComponent::soundChannel = 0;

AudioPlayerComponent::AudioPlayerComponent(const string& strSoundName)
{
	audio.LoadSound(strSoundName, true, false, 1.0);
	//soundChannel = audio.PlaySounds(strSoundName, Vector3{ gameObject->transform.position.x,gameObject->transform.position.y,gameObject->transform.position.z }, 1.0);
	audio.StopChannel(soundChannel);
}

void AudioPlayerComponent::volume(float volumedB)
{
	audio.SetChannelVolume(soundChannel, volumedB);
}

void AudioPlayerComponent::update(float deltaTime)
{
	audio.SetChannel3dPosition(soundChannel, Vector3{ gameObject->transform.position.x,gameObject->transform.position.y,gameObject->transform.position.z });
}