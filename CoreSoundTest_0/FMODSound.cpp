#include "FMODSound.hpp"

bool FMODSound::initialize()
{
	//FMOD_RESULT rst = FMOD::System_Create(&m_pFmodSystem);
	//if (rst != FMOD_OK)
	//{
	//	OutputDebugString(L"WanyCore::FMODSound::Initialize::Failed Create System.");
	//	return false;
	//}

	//rst = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0); // 32: 최대 32개 까지 동시 출력 할 수 있다. 더 많이 사용 할 수 있으나 현 수준에선 32개 이상 불필요.
	//if (rst != FMOD_OK)
	//{
	//	OutputDebugString(L"WanyCore::FMODSound::Initialize::Failed Initialize System.");
	//	return false;
	//}

	return true;
}

bool FMODSound::setSystem(FMOD::System* _system)
{
	m_pFmodSystem = _system;
	return true;
}

bool FMODSound::load(std::string _filename)
{
	// 사운드 파일 로드
	FMOD_RESULT rst = m_pFmodSystem->createSound(_filename.c_str(), FMOD_DEFAULT, nullptr, &m_pSound);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::load::Failed Load FMODSound File.");
		return false;
	}

	m_pSound->getLength(&totalTime, FMOD_TIMEUNIT_MS);

	return true;
}

bool FMODSound::play()
{
	bool isPlaying = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&isPlaying);
	}
	else
	{
		return false;
	}

	if (!isPlaying)
	{
		// 사운드 실행. 실행되어야 채널에 반환됨.
		// 만약 이미 출력 중이면, 다른 채널에서 출력이 됨.
		FMOD_RESULT rst = m_pFmodSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (rst != FMOD_OK)
		{
			OutputDebugString(L"WanyCore::FMODSound::play::Failed Play FMODSound.");
			return false;
		}

	}

	return true;
}

bool FMODSound::playEffect()
{
	// Effect 사운드는 연발로 출력이 가능해야 하기 때문에 
	// 플레이 중인지에 관계없이 동일한 채널을 반환해 줘야 한다.
	FMOD_RESULT rst = m_pFmodSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::play::Failed Play FMODSound.");
		return false;
	}

	return true;
}

bool FMODSound::pause()
{
	if (m_pChannel == nullptr)
	{
		return false;
	}

	bool paused;
	FMOD_RESULT rst = m_pChannel->getPaused(&paused);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::pause::Failed Get Paused Flag.");
		return false;
	}

	rst = m_pChannel->setPaused(!paused);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::pause::Failed Set Paused Flag.");
		return false;
	}

	return true;
}

bool FMODSound::stop()
{
	FMOD_RESULT rst = m_pChannel->stop();
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::stop::Failed Stop FMODSound.");
		return false;
	}

	return true;
}

bool FMODSound::setVolume(float _volume)
{
	// 볼륨 값은 0 ~ 1 값 사이로 넣어야 함.
	FMOD_RESULT rst = m_pChannel->setVolume(_volume);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::setVolume::Failed Set Volume.");
		return false;
	}

	return true;
}

bool FMODSound::volumeUp(float _volume)
{
	// 볼륨 값은 0 ~ 1 값 사이로 넣어야 함.
	float val = 0.0f;
	FMOD_RESULT rst = m_pChannel->getVolume(&val);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::volumeUp::Failed Get Volume.");
		return false;
	}

	val += _volume;
	val = val > 1.0f ? 1.0f : val;
	val = val < 0.0f ? 0.0f : val;

	rst = m_pChannel->setVolume(val);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::volumeUp::Failed Set Volume.");
		return false;
	}

	return true;
}

bool FMODSound::volumeDown(float _volume)
{
	float val = 0.0f;
	FMOD_RESULT rst = m_pChannel->getVolume(&val);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::volumeDown::Failed Get Volume.");
		return false;
	}

	val -= _volume;
	val = val > 1.0f ? 1.0f : val;
	val = val < 0.0f ? 0.0f : val;

	rst = m_pChannel->setVolume(val);
	if (rst != FMOD_OK)
	{
		OutputDebugString(L"WanyCore::FMODSound::volumeDown::Failed Set Volume.");
		return false;
	}
	return false;
}

bool FMODSound::setLoop(bool _loop)
{
	FMOD_RESULT rst;
	if (_loop)
	{
		rst = m_pSound->setMode(FMOD_LOOP_NORMAL); // 무한 재생
		if (rst != FMOD_OK)
		{
			OutputDebugString(L"WanyCore::FMODSound::setLoop::Failed Set Mode.");
			return false;
		}
	}
	else
	{
		rst = m_pSound->setMode(FMOD_LOOP_OFF); // 무한 재생 해제
		if (rst != FMOD_OK)
		{
			OutputDebugString(L"WanyCore::FMODSound::setLoop::Failed Set Mode.");
			return false;
		}
	}

	return false;
}

bool FMODSound::frame()
{
	// Frame에 꼭 있어야 함. FMODSound file 크기에 따라 파일을 전부 읽어오는 경우가 있고, 부분만 읽어오는 경우가 있어
	// frame 에서 주기적으로 update를 이용하여 파일을 추가적으로 읽어옴.
	

	if (m_pChannel != nullptr)
	{
		unsigned int ms = 0;
		FMOD_RESULT rst = m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
		if (rst != FMOD_OK)
		{
			OutputDebugString(L"WanyCore::FMODSound::frame::Failed Get FMODSound Position.");
			return false;
		}

		TCHAR szBuffer[256] = { 0, };
		/*_stprintf_s(szBuffer, _T("경과 시간[%02d:%02d:%02d], 전체 시간[%02d:%02d:%02d]"),
			(ms / 1000) / 60, (ms / 1000) % 60, (ms / 10) % 60,
			(totalTime / 1000) / 60, (totalTime / 1000) % 60, (totalTime / 10) % 60);*/
	}

	return true;
}

bool FMODSound::render()
{
	// 사운드 실행. 실행되어야 채널에 반환됨.
	//FMOD_RESULT rst = m_pFmodSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	return true;
}

bool FMODSound::release()
{
	//if (m_pSound != nullptr)
	//{
	//	m_pSound->release();
	//	m_pSound = nullptr;
	//}

	//if (m_pFmodSystem != nullptr)
	//{
	//	// System은 Close 먼저 필요함.
	//	m_pFmodSystem->close();
	//	m_pFmodSystem->release();
	//	m_pFmodSystem = nullptr;
	//}
	return true;
}
