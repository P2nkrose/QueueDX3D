#pragma once
#include <Engine/qState.h>

class qFireState : public qState
{
public:
	CLONE(qFireState);
	qFireState();
	~qFireState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

