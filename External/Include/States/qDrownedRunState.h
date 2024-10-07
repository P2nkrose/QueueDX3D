#pragma once
#include <Engine/qState.h>

class qGameObject;

class qDrownedRunState : public qState
{
public:
	CLONE(qDrownedRunState);
	qDrownedRunState();
	~qDrownedRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float			m_Speed;

	Vec3			OGScale;
	Vec3			OGColScale;
};

