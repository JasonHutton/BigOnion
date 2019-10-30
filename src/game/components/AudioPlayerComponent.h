#pragma once
#include "../src/engine/audio/AudioEngine.h"
#include "../src/engine/ECS/Component.h"

class AudioPlayerComponent:
	public Component
{
public:
	static const std::string typeID;
	static int soundChannel;
	AudioPlayerComponent(const string& strSoundName);

	void update(float deltaTime) override;
	void volume(float volumedB);
	std::string componentTypeID() override { return typeID; }

private:
	AudioEngine audio;
};