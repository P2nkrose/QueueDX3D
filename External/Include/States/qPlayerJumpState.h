#pragma once
#include <Engine/qState.h>

class qPlayerJumpState : public qState
{
public:
	CLONE(qPlayerJumpState);
	qPlayerJumpState();
	~qPlayerJumpState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

