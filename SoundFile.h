#pragma once

#include "File.h"
#include "../src/engine/audio/AudioEngine.h"

class SoundFile : public File
{
public:
	SoundFile(AudioEngine* audio, const string& iFile = "", const string& explicitPath = "");

public:
	const Vector3 GetPosition() const;
	const void SetPosition(Vector3 v3Pos);

	const void load(bool b3d = false, bool bLooping = false, bool bStream = false);
	
	const void play() const;
	const void play(bool volumeTodB) const;
	const void play(Vector3 v3Pos, bool volumeTodB) const;

private:
	AudioEngine* audioEngine;
	Vector3 v3Position;

public:
	bool is3D;
	bool isLooping;
	bool isStream;
	float volumedB;
};