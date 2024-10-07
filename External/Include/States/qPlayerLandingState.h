#pragma once
#include <Engine/qState.h>

class qPlayerLandingState : public qState
{
public:
	CLONE(qPlayerLandingState);
	qPlayerLandingState();
	~qPlayerLandingState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


};

