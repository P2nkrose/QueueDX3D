#pragma once
#include <Engine/qState.h>

class qPostOpenState : public qState
{
public:
	CLONE(qPostOpenState);
	qPostOpenState();
	~qPostOpenState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

