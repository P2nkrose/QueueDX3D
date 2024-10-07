#pragma once
#include <Engine/qState.h>

class qElevatorOpenState : public qState
{
public:
	CLONE(qElevatorOpenState);
	qElevatorOpenState();
	~qElevatorOpenState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

