#include "FMODSoundManager.hpp"

bool FMODSoundManager::Load(std::wstring _filename, SoundType _type)
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
		delete newSound;

		std::wstring debugStr = L"WanyCore::FMODSoundManager::Load::Failed Load FMODSound(";
		debugStr += _filename + L").\n";
		OutputDebugString(debugStr.c_str());
		return false;
	}

	if (_type == SoundType::Effect)
	{
		newSound->setLoop(false);
	}
	else
	{
		newSound->setLoop(true);
	}
	
	m_SoundList.insert(std::make_pair(_filename, newSound));

	return true;
}

bool FMODSoundManager::LoadDir(std::wstring _path)
{
	// recursive_directory_iterator ��� �� ���� �������� ��� Ž��.
	/*std::filesystem::path path(_path);
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring str = file.path();
		Load(str);
	}*/

	// directory_iterator ��� �� ���� ������ Ž��. ���� ���� Ž�� �� ��������� ���� ȣ�� �ʿ�.
	// ���� �ڵ�� �Ʒ� �ڵ尡 �����ϴٰ� ���� ��.
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filename = file.path().filename();
		std::wstring str = file.path();
		if (file.path().extension() == L"")
		{
			std::wstring dir = str + L"/";
			LoadDir(dir);
		}
		else
		{
			Load(str);
		}
	}

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

	rst = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0); // 32: �ִ� 32�� ���� ���� ��� �� �� �ִ�. �� ���� ��� �� �� ������ �� ���ؿ��� 32�� �̻� ���ʿ�.
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

	return true;
}

bool FMODSoundManager::render()
{
	return false;
}

bool FMODSoundManager::release()
{
	for (auto it : m_SoundList)
	{
		FMODSound* pSound = it.second;
		pSound->release();
		delete pSound;
		pSound = nullptr;
	}

	if (m_pFmodSystem != nullptr)
	{
		// System�� Close ���� �ʿ���.
		m_pFmodSystem->close();
		m_pFmodSystem->release();
		m_pFmodSystem = nullptr;
	}

	return false;
}