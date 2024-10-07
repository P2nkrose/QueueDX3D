#pragma once
#include <Engine/qState.h>

class qPlayerElevatorOutState : public qState
{
public:
	CLONE(qPlayerElevatorOutState);
	qPlayerElevatorOutState();
	~qPlayerElevatorOutState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

