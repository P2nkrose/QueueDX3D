#pragma once
#include <Engine/qState.h>

class qElevatorCloseState : public qState
{
public:
	CLONE(qElevatorCloseState);
	qElevatorCloseState();
	~qElevatorCloseState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

