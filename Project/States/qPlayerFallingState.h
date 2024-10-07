#pragma once
#include <Engine/qState.h>

class qPlayerFallingState : public qState
{
public:
	CLONE(qPlayerFallingState);
	qPlayerFallingState();
	~qPlayerFallingState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

