#include "pch.h"
#include "qSound.h"

#include "qAssetMgr.h"

FMOD_RESULT CHANNEL_CALLBACK(FMOD_CHANNELCONTROL* channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype
	, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype
	, void* commanddata1, void* commanddata2);


qSound::qSound()
	: qAsset(ASSET_TYPE::SOUND)
	, m_Sound(nullptr)
{
}

qSound::~qSound()
{
	if (nullptr != m_Sound)
	{
		FMOD_RESULT result = m_Sound->release();
		m_Sound = nullptr;
	}
}

int qSound::Play(int _iRoopCount, float _fVolume, bool _bOverlap)
{
	if (_iRoopCount <= -1)
	{
		assert(nullptr);
	}

	// 재생되고 있는 채널이 있는데, 중복재생을 허용하지 않았다 -> 재생 안함
	if (!_bOverlap && !m_listChannel.empty())
	{
		return E_FAIL;
	}

	_iRoopCount -= 1;

	FMOD::Channel* pChannel = nullptr;
	qEngine::GetInst()->GetFMODSystem()->playSound(m_Sound, nullptr, false, &pChannel);

	// 재생 실패
	if (nullptr == pChannel)
		return E_FAIL;

	pChannel->setVolume(_fVolume);

	pChannel->setCallback(&CHANNEL_CALLBACK);
	pChannel->setUserData(this);

	pChannel->setMode(FMOD_LOOP_NORMAL);
	pChannel->setLoopCount(_iRoopCount);

	m_listChannel.push_back(pChannel);

	int iIdx = -1;
	pChannel->getIndex(&iIdx);

	return iIdx;
}


void qSound::Stop()
{
	list<FMOD::Channel*>::iterator iter;

	while (!m_listChannel.empty())
	{
		iter = m_listChannel.begin();
		(*iter)->stop();
	}
}

bool qSound::IsSoundFinished()
{
	bool isPlaying = false;
	list<FMOD::Channel*>::iterator iter = m_listChannel.begin();

	// 재생 중인 모든 채널을 확인
	for (; iter != m_listChannel.end(); ++iter)
	{
		if (*iter != nullptr)
		{
			// 사운드가 재생 중인지 확인
			(*iter)->isPlaying(&isPlaying);

			// 만약 하나라도 재생 중이라면 false 반환
			if (isPlaying)
			{
				return false;
			}
		}
	}

	// 모든 채널에서 사운드가 끝났다면 true 반환
	return true;
}


void qSound::SetVolume(float _f, int _iChannelIdx)
{
	list<FMOD::Channel*>::iterator iter = m_listChannel.begin();

	int iIdx = -1;
	for (; iter != m_listChannel.end(); ++iter)
	{
		(*iter)->getIndex(&iIdx);
		if (_iChannelIdx == iIdx)
		{
			(*iter)->setVolume(_f);
			return;
		}
	}
}



int qSound::Load(const wstring& _FilePath)
{
	string path(_FilePath.begin(), _FilePath.end());

	if (FMOD_OK != qEngine::GetInst()->GetFMODSystem()->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &m_Sound))
	{
		assert(nullptr);
	}

	return S_OK;
}

int qSound::Save(const wstring& _FilePath)
{
	return S_OK;
}



void qSound::RemoveChannel(FMOD::Channel* _pTargetChannel)
{
	list<FMOD::Channel*>::iterator iter = m_listChannel.begin();
	for (; iter != m_listChannel.end(); ++iter)
	{
		if (*iter == _pTargetChannel)
		{
			m_listChannel.erase(iter);
			return;
		}
	}
}









// =========
// Call Back
// =========
FMOD_RESULT CHANNEL_CALLBACK(FMOD_CHANNELCONTROL* channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype
	, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype
	, void* commanddata1, void* commanddata2)
{
	FMOD::Channel* cppchannel = (FMOD::Channel*)channelcontrol;
	qSound* pSound = nullptr;

	switch (controltype)
	{
	case FMOD_CHANNELCONTROL_CALLBACK_END:
	{
		cppchannel->getUserData((void**)&pSound);
		pSound->RemoveChannel(cppchannel);
	}
	break;
	}

	return FMOD_OK;
}