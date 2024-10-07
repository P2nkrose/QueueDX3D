#pragma once
#include <Engine/qState.h>

class qDoorOpenState : public qState
{
public:
	CLONE(qDoorOpenState);
	qDoorOpenState();
	~qDoorOpenState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

