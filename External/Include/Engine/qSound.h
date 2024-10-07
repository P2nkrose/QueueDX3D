#pragma once
#include "qAsset.h"

class qSound : public qAsset
{
public:
	qSound();
	~qSound();

public:
	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;

public:
	// _iRoopCount : 0 (무한반복),  _fVolume : 0 ~ 1(Volume), _bOverlap : 소리 중첩 가능여부
	int Play(int _iRoopCount, float _fVolume, bool _bOverlap);
	void RemoveChannel(FMOD::Channel* _pTargetChannel);
	void Stop();

	bool IsSoundFinished();

	// 0 ~ 1
	void SetVolume(float _f, int _iChannelIdx);

private:
	FMOD::Sound*			m_Sound;        // Sound 버퍼
	list<FMOD::Channel*>	m_listChannel;  // Sound 가 재생되고 있는 채널 리스트
};

