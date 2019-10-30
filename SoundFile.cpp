#include "SoundFile.h"

SoundFile::SoundFile(AudioEngine* audio, const string& iFile, const string& explicitPath) : audioEngine(audio), File(iFile, explicitPath)
{
	SetPosition(Vector3{ 0, 0, 0 });
	this->is3D = false;
	this->isLooping = false;
	this->isStream = false;
	this->volumedB = 1.0f;
}

const Vector3 SoundFile::GetPosition() const
{
	return this->v3Position;
}
const void SoundFile::SetPosition(Vector3 v3Pos)
{
	this->v3Position = v3Pos;
}

const void SoundFile::load(bool b3d, bool bLooping, bool bStream)
{
	//audioEngine->LoadSound(this->GetOSPath(), b3d, bLooping, bStream);
}

const void SoundFile::play() const
{
	this->play(this->v3Position, this->volumedB);
}

const void SoundFile::play(bool volumeTodB) const
{
	this->play(this->v3Position, volumeTodB);
}

const void SoundFile::play(Vector3 v3Pos, bool volumeTodB) const
{
	//audioEngine->PlaySounds(this->GetOSPath(), v3Pos, volumeTodB);
}