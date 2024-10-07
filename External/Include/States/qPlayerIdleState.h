#pragma once
#include <Engine/qState.h>


class qPlayerIdleState : public qState
{
public:
	CLONE(qPlayerIdleState);
	qPlayerIdleState();
	~qPlayerIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float		WaitTime;
};

