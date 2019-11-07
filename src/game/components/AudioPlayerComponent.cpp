#include "AudioPlayerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"

const std::string AudioPlayerComponent::typeID = "Audio";
int AudioPlayerComponent::soundChannel = 0;
bool surround, looping, streaming;
string soundName;

AudioPlayerComponent::AudioPlayerComponent(const string& strSoundName, bool is3D, bool isLooping, bool isStreaming)
{
	soundName = strSoundName;
	surround = is3D;
	looping = isLooping;
	streaming = isStreaming;
}

void AudioPlayerComponent::onAddToGameWorld()
{
	soundChannel = audio.LoadSound(soundName, convert(gameObject->transform.position), audio.VolumeTodB(1.0f), surround, looping, streaming);
}

Vector3 AudioPlayerComponent::convert(Vector3f vPos)
{
	Vector3 vector = Vector3{ vPos.x,vPos.y,vPos.z };
	return vector;
}

void AudioPlayerComponent::play()
{
	audio.PlaySounds(soundChannel);
}

void AudioPlayerComponent::stop()
{
	audio.StopSounds(soundChannel);
}

void AudioPlayerComponent::pause()
{
	audio.PauseSounds(soundChannel);
}

void AudioPlayerComponent::volume(float volume)
{
	audio.SetVolume(soundChannel, audio.VolumeTodB(volume));
}

void AudioPlayerComponent::update(float deltaTime)
{
	audio.SetChannel3dPosition(soundChannel, convert(gameObject->transform.position));
}