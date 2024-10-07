#pragma once
#include <Engine/qState.h>

class qPlayerDashState : public qState
{
public:
	CLONE(qPlayerDashState);
	qPlayerDashState();
	~qPlayerDashState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	Vec3		OGScale;
	Vec3		OGColScale;
	Vec3		OGPos;

	float		m_DashSpeed;
	float		m_MaxRange;

	bool		soundflag;
};

