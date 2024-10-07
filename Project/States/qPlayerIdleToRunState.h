#pragma once
#include <Engine/qState.h>

class qPlayerIdleToRunState : public qState
{
public:
	CLONE(qPlayerIdleToRunState);
	qPlayerIdleToRunState();
	~qPlayerIdleToRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

