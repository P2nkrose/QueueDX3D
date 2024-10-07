#pragma once
#include <Engine/qState.h>

class qBossStayState : public qState
{
public:
	CLONE(qBossStayState);
	qBossStayState();
	~qBossStayState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

