#pragma once
#include "FMODSound.hpp"

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
	bool Load(std::wstring _filename);
	FMODSound* getSound(std::wstring _filename);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();

};