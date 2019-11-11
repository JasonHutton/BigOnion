#include "AudioPlayerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"

const std::string AudioPlayerComponent::typeID = "Audio";
int AudioPlayerComponent::soundChannel = 0;
float fVolume;
bool surround, looping, streaming;
string soundName;

AudioPlayerComponent::AudioPlayerComponent(AudioEngine audio, const string& strSoundName,float volumeDb, bool is3D, bool isLooping, bool isStreaming)
{
	soundName = strSoundName;
	surround = is3D;
	looping = isLooping;
	streaming = isStreaming;
	fVolume = volumeDb;
}

void AudioPlayerComponent::onAddToGameWorld()
{
	soundChannel = audio.LoadSound(soundName, convert(gameObject->transform.position), fVolume, surround, looping, streaming);
	audio.PlaySounds(soundChannel);
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

void AudioPlayerComponent::volume(float volume, bool isMusic)
{
	audio.SetVolume(soundChannel, audio.VolumeTodB(volume), isMusic);
}

void AudioPlayerComponent::setSpeed(float speed, bool isMusic)
{
	audio.SetSpeed(soundChannel, speed / 50 + 1);
	audio.SetVolume(soundChannel, audio.VolumeTodB(speed / 50 + fVolume), isMusic);
}

void AudioPlayerComponent::update(float deltaTime)
{
	audio.SetChannel3dPosition(soundChannel, convert(gameObject->transform.position));
}

void AudioPlayerComponent::pauseExec()
{
	pause();
}

void AudioPlayerComponent::unpauseExec()
{
	play();
}
