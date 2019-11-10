#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Implementation {
	Implementation();
	~Implementation();

	void Update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	int mnNextChannelId;

	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;
	typedef map<string, FMOD::Studio::EventInstance*> EventMap;
	typedef map<string, FMOD::Studio::Bank*> BankMap;
	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};

class AudioEngine {
public:
	static void Init();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result);

	
	void UnLoadSound(const string& strSoundName);
	void Set3dListenerAndOrientation(const Vector3& vPosition, const Vector3& vVel, const Vector3& vLook, const Vector3& vUp);
	int LoadSound(const string& strSoundName, const Vector3& vPosition, float fVolumedB, bool b3d, bool bLooping, bool bStream);
	void PlaySounds(int nChannelId);
	void StopSounds(int nChannelId);
	void PauseSounds(int nChannelId);
	//void StopAllChannels();
	void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
	void SetVolume(int nChannelId, float fVolumedB);
	void SetSpeed(int nChannelId, float speed);
	bool IsPlaying(int nChannelId);
	float dbToVolume(float dB);
	float VolumeTodB(float volume);
	
private:
	void ConfigSound(const string& strSoundName, bool b3d, bool bLooping, bool bStream);
	FMOD_VECTOR VectorToFmod(const Vector3& vPosition);
	
};

#endif