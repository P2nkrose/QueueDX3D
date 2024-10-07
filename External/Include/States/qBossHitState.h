#pragma once
#include <Engine/qState.h>

class qBossHitState : public qState
{
public:
	CLONE(qBossHitState);
	qBossHitState();
	~qBossHitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	float				m_BossBumpSpeed;
	float				m_MaxRange;

	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;
};

