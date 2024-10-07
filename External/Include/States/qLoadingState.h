#pragma once
#include <Engine/qState.h>

class qLoadingState : public qState
{
public:
	CLONE(qLoadingState);
	qLoadingState();
	~qLoadingState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

