#pragma once
#include "../src/engine/audio/AudioEngine.h"
#include "../src/engine/ECS/Component.h"
#include "../../engine/utils/Vector3.h"

class AudioPlayerComponent:
	public Component
{
public:
	static const std::string typeID;
	int soundChannel;
	AudioPlayerComponent(AudioEngine audio, const string& strSoundName,float volumeDb, bool is3D, bool isLooping, bool isStreaming);

	void play();
	void stop();
	void pause();
	void setSpeed(float speed, bool isMusic = false);
	void onAddToGameWorld() override;
	void update(float deltaTime) override;
	void pauseExec() override;
	void unpauseExec() override;
	void volume(float volume, bool isMusic = false);
	void playEffect();
	std::string componentTypeID() override { return typeID; }

private:
	AudioEngine audio;
	Vector3 convert(Vector3f vPos);
	void wait(int seconds);
};