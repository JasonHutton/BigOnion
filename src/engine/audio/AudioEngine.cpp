#include "AudioEngine.h"

Implementation::Implementation() {
	mpStudioSystem = NULL;
	AudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	AudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

	mpSystem = NULL;
	AudioEngine::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
}

Implementation::~Implementation() {
	AudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
	AudioEngine::ErrorCheck(mpStudioSystem->release());
}

void Implementation::Update() {
	vector<ChannelMap::iterator> pStoppedChannels;
	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
	{
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		if (!bIsPlaying)
		{
			pStoppedChannels.push_back(it);
		}
	}
	for (auto& it : pStoppedChannels)
	{
		mChannels.erase(it);
	}
	AudioEngine::ErrorCheck(mpStudioSystem->update());
}

Implementation* sgpImplementation = nullptr;

void AudioEngine::Init() {
	sgpImplementation = new Implementation;
}

void AudioEngine::Update() {
	sgpImplementation->Update();
}

void AudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt != sgpImplementation->mSounds.end())
		return;
	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	FMOD::Sound* pSound = nullptr;
	AudioEngine::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound) {
		sgpImplementation->mSounds[strSoundName] = pSound;
	}
}

void AudioEngine::UnLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
		return;
	AudioEngine::ErrorCheck(tFoundIt->second->release());
	sgpImplementation->mSounds.erase(tFoundIt);
}

int AudioEngine::PlaySounds(const string& strSoundName, const Vector3& vPosition, float fVolumedB)
{
	int nChannelId = sgpImplementation->mnNextChannelId++;
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
	{
		LoadSound(strSoundName);
		tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			return nChannelId;
		}
	}
	FMOD::Channel* pChannel = nullptr;
	AudioEngine::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{
		FMOD_MODE currMode;
		tFoundIt->second->getMode(&currMode);
		if (currMode & FMOD_3D) {
			FMOD_VECTOR position = VectorToFmod(vPosition);
			AudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
		}
		AudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
		AudioEngine::ErrorCheck(pChannel->setPaused(false));
		sgpImplementation->mChannels[nChannelId] = pChannel;
	}
	return nChannelId;
}

void AudioEngine::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	FMOD_VECTOR position = VectorToFmod(vPosition);
	AudioEngine::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

void AudioEngine::SetChannelVolume(int nChannelId, float fVolumedB)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	AudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

void AudioEngine::StopChannel(int nChannelId)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;
	AudioEngine::ErrorCheck(tFoundIt->second->stop());
}

FMOD_VECTOR AudioEngine::VectorToFmod(const Vector3& vPosition) {
	FMOD_VECTOR fVec;
	fVec.x = vPosition.x;
	fVec.y = vPosition.y;
	fVec.z = vPosition.z;
	return fVec;
}

int AudioEngine::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		cout << "FMOD ERROR " << result << endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}

float  AudioEngine::dbToVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

float  AudioEngine::VolumeTodB(float volume)
{
	return 20.0f * log10f(volume);
}

void AudioEngine::Shutdown() {
	delete sgpImplementation;
}