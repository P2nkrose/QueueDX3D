#pragma once
#include <Engine/qState.h>

class qPostCloseState : public qState
{
public:
	CLONE(qPostCloseState);
	qPostCloseState();
	~qPostCloseState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

