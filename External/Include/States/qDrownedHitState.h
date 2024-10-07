#pragma once
#include <Engine/qState.h>

class qDrownedHitState : public qState
{
public:
	CLONE(qDrownedHitState);
	qDrownedHitState();
	~qDrownedHitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	float			m_DrownedBumpSpeed;
	float			m_MaxRange;
	Vec3			OGScale;
	Vec3			OGColScale;

};

