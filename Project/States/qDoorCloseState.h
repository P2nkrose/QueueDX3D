#pragma once
#include <Engine/qState.h>

class qDoorCloseState : public qState
{
public:
	CLONE(qDoorCloseState);
	qDoorCloseState();
	~qDoorCloseState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

