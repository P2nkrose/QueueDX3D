#pragma once
#include <Engine/qState.h>

class qPlayerRunState : public qState
{
public:
	CLONE(qPlayerRunState);
	qPlayerRunState();
	~qPlayerRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

