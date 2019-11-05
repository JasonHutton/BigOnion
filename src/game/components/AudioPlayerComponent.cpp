#include "AudioPlayerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"

const std::string AudioPlayerComponent::typeID = "Audio";
int AudioPlayerComponent::soundChannel = 0;

AudioPlayerComponent::AudioPlayerComponent(const string& strSoundName, Vector3f vPos, bool is3D, bool isLooping, bool isStreaming)
{
	soundChannel = audio.LoadSound(strSoundName, convert(vPos), audio.VolumeTodB(1.0f), is3D, isLooping, isStreaming);
	audio.PlaySounds(soundChannel);
	//cout << convert(vPos).x << convert(vPos).y << convert(vPos).z;
}

Vector3 AudioPlayerComponent::convert(Vector3f vPos)
{
	Vector3 vector = Vector3{ vPos.x,vPos.y,vPos.z };
	return vector;
}

void AudioPlayerComponent::play(int channelID)
{
	audio.PlaySounds(channelID);
}

void AudioPlayerComponent::stop(int channelID)
{
	audio.StopSounds(channelID);
}

void AudioPlayerComponent::pause(int channelID)
{
	audio.PauseSounds(channelID);
}

void AudioPlayerComponent::volume(float volumedB)
{
	audio.SetVolume(soundChannel, audio.VolumeTodB(volumedB));
}

void AudioPlayerComponent::update(float deltaTime)
{
	//audio.SetChannel3dPosition(soundChannel,position);
}