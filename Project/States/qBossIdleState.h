#pragma once
#include <Engine/qState.h>

class qBossIdleState : public qState
{
public:
	CLONE(qBossIdleState);
	qBossIdleState();
	~qBossIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float				m_DetectRange;
	float				m_AttackRange;

	float				m_Time;

	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;

	bool				UturnFlag;

};

