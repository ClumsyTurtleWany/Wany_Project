#include "FMODSoundManager.hpp"

bool FMODSoundManager::Load(std::wstring _filename)
{
	auto it = m_SoundList.find(_filename);
	if (it != m_SoundList.end())
	{
		return true;
	}

	FMODSound* newSound = new FMODSound;
	newSound->setSystem(m_pFmodSystem);
	newSound->initialize();
	std::string filename;
	filename.assign(_filename.begin(), _filename.end());
	if (!newSound->load(filename))
	{
		std::wstring debugStr = L"WanyCore::FMODSoundManager::Load::Failed Load FMODSound(";
		debugStr += _filename + L").\n";
		OutputDebugString(debugStr.c_str());
		return false;
	}
	
	m_SoundList.insert(std::make_pair(_filename, newSound));

	return true;
}

FMODSound* FMODSoundManager::getSound(std::wstring _filename)
{
	auto it = m_SoundList.find(_filename);
	if (it != m_SoundList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool FMODSoundManager::initialize()
{
	FMOD_RESULT rst = FMOD::System_Create(&m_pFmodSystem);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSoundManager::Initialize::Failed Create System.");
		return false;
	}

	rst = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0); // 32: 최대 32개 까지 동시 출력 할 수 있다. 더 많이 사용 할 수 있으나 현 수준에선 32개 이상 불필요.
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSoundManager::Initialize::Failed Initialize System.");
		return false;
	}

	return true;
}

bool FMODSoundManager::frame()
{
	FMOD_RESULT rst = m_pFmodSystem->update();
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::frame::Failed Update FMODSound System.");
		return false;
	}

	return false;
}

bool FMODSoundManager::render()
{
	return false;
}

bool FMODSoundManager::release()
{
	return false;
}
