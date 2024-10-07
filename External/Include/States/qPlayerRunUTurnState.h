#pragma once
#include <Engine/qState.h>

class qPlayerRunUTurnState : public qState
{
public:
	CLONE(qPlayerRunUTurnState);
	qPlayerRunUTurnState();
	~qPlayerRunUTurnState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

