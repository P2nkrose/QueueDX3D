#pragma once
#include <Engine/qState.h>

class qGameObject;

class qSkeletonIdleState : public qState
{
public:
	CLONE(qSkeletonIdleState);
	qSkeletonIdleState();
	~qSkeletonIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qGameObject*	m_Bang;
	float			m_BangTime;
	bool			Bangflag;
	
	float			m_DetectRange;
	
	float			m_SoundRange;
	bool			soundflag;
};

