#pragma once
#include "../src/engine/audio/AudioEngine.h"
#include "../src/engine/ECS/Component.h"
#include "../../engine/utils/Vector3.h"

class AudioPlayerComponent:
	public Component
{
public:
	static const std::string typeID;
	static int soundChannel;
	AudioPlayerComponent(const string& strSoundName, Vector3f vPos, bool is3D, bool isLooping, bool isStreaming);

	void play(int channelID);
	void stop(int channelID);
	void pause(int channelID);
	void update(float deltaTime) override;
	void volume(float volumedB);
	std::string componentTypeID() override { return typeID; }

private:
	AudioEngine audio;
	Vector3 convert(Vector3f vPos);
};