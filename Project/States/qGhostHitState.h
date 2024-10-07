#pragma once
#include <Engine/qState.h>

class qGhostHitState : public qState
{
public:
	CLONE(qGhostHitState);
	qGhostHitState();
	~qGhostHitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	float			m_GhostBumpSpeed;
	float			m_MaxRange;
	Vec3			OGScale;
	Vec3			OGColScale;
};

