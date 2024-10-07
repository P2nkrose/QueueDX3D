#pragma once
#include <Engine/qState.h>

class qBossSlamFistState : public qState
{
public:
	CLONE(qBossSlamFistState);
	qBossSlamFistState();
	~qBossSlamFistState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

