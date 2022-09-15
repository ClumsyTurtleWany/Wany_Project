#pragma once

//www.fmod.com -> Download -> Windows
//C:\Program Files(x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core
// inc, lib
#include "fmod/fmod.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

#include "Define.hpp"

class FMODSound
{
public:
	FMOD::System*	m_pFmodSystem = nullptr;
	FMOD::Sound*	m_pSound; // ���� ���� ex).mp3, .wav, ...
	FMOD::Channel*	m_pChannel; // �ϳ��� ���尡 ���� ����Ŀ�� �л�Ǿ ������ ��. ������ ����ϴ� ��.

public:
	unsigned int totalTime;

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();

public:
	bool setSystem(FMOD::System* _system);
	bool load(std::string _filename);
	bool play();
	bool playEffect();
	bool pause();
	bool stop();
	bool setVolume(float _volume);
	bool volumeUp(float _volume);
	bool volumeDown(float _volume);
	bool setLoop(bool _loop);
};