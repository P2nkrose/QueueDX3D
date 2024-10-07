#pragma once
#include <Engine/qState.h>

class qGameObject;

class qGhostRunState : public qState
{
public:
	CLONE(qGhostRunState);
	qGhostRunState();
	~qGhostRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	float			m_Speed;

};

