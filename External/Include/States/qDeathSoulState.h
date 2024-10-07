#pragma once
#include <Engine/qState.h>

class qDeathSoulState : public qState
{
public:
	CLONE(qDeathSoulState);
	qDeathSoulState();
	~qDeathSoulState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

