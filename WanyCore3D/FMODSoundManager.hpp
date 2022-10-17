#pragma once
#include "FMODSound.hpp"

enum class SoundType
{
	BGM,
	Effect,
};

class FMODSoundManager : public Singleton<FMODSoundManager>
{
private:
	friend class Singleton<FMODSoundManager>;
	FMOD::System* m_pFmodSystem = nullptr;

	std::map<std::wstring, FMODSound*> m_SoundList;

private:
	FMODSoundManager() {};
	~FMODSoundManager() { release(); };

public:
	bool Load(std::wstring _filename, SoundType _type = SoundType::Effect);
	bool LoadDir(std::wstring _path);
	FMODSound* getSound(std::wstring _filename);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();

};