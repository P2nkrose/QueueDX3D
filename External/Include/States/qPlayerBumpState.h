#pragma once
#include <Engine/qState.h>

class qPlayerBumpState : public qState
{
public:
	CLONE(qPlayerBumpState);
	qPlayerBumpState();
	~qPlayerBumpState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float		m_BumpSpeed;
	float		m_MaxRange;

	bool		soundflag;
};

