#pragma once
#include "src/engine/ECS/Component.h"
#include "src/engine/audio/AudioEngine.h"

class AudioPlayerComponent:
	public Component
{
public:
	static const std::string typeID;
	AudioPlayerComponent(AudioEngine*);

	void update(float deltaTime) override;
	std::string componentTypeID() override { return typeID; }
private:
	AudioEngine* audio;
};