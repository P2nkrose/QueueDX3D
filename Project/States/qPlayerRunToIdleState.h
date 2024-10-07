#pragma once
#include <Engine/qState.h>

class qPlayerRunToIdleState : public qState
{
public:
	CLONE(qPlayerRunToIdleState);
	qPlayerRunToIdleState();
	~qPlayerRunToIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

