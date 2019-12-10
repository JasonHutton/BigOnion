#include "AudioPlayerComponent.h"
#include "../src/engine/ECS/GameObject.h"
#include "../src/engine/ECS/GameWorld.h"
#include <time.h>
#include <thread>         
#include <chrono>        


const std::string AudioPlayerComponent::typeID = "Audio";
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
	soundChannel = 0;
}

AudioPlayerComponent::~AudioPlayerComponent()
{
	audio.Shutdown();
	audio.Init();
}

void AudioPlayerComponent::onAddToGameWorld()
{
	soundChannel = audio.LoadSound(soundName, convert(gameObject->transform.position), fVolume, surround, looping, streaming);
	printf("Sound Name: %s, Sound Channel: %d\n", soundName.c_str(), soundChannel);
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

void AudioPlayerComponent::playEffect()
{
	audio.RestartSound(soundName, soundChannel);
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
	//printf("Position: %f, %f,%f \n", gameObject->transform.position.x, gameObject->transform.position.y, gameObject->transform.position.z);
}

void AudioPlayerComponent::pauseExec()
{
	pause();
}

void AudioPlayerComponent::unpauseExec()
{
	//play();
}

void AudioPlayerComponent::wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	//std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	while (clock() < endwait) {}
}

void AudioPlayerComponent::stopAll()
{
	audio.StopAllChannels();
}
