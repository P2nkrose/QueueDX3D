#pragma once
#include <Engine/qState.h>

class qPlayerIdleUTurnState : public qState
{
public:
	CLONE(qPlayerIdleUTurnState);
	qPlayerIdleUTurnState();
	~qPlayerIdleUTurnState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

