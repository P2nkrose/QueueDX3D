#pragma once
#include <Engine/qState.h>

class qGameObject;

class qDrownedIdleState : public qState
{
public:
	CLONE(qDrownedIdleState);
	qDrownedIdleState();
	~qDrownedIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qGameObject*	m_Bang;

	float			m_DetectRange;
	float			m_AttackRange;

	bool			Bangflag;
};

