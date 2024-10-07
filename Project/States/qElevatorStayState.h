#pragma once
#include <Engine/qState.h>

class qElevatorStayState : public qState
{
public:
	CLONE(qElevatorStayState);
	qElevatorStayState();
	~qElevatorStayState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

