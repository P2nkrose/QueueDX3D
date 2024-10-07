#pragma once
#include <Engine/qState.h>

class qDoorStayState : public qState
{
public:
	CLONE(qDoorStayState);
	qDoorStayState();
	~qDoorStayState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

