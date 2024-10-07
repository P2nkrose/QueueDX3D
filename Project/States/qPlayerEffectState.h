#pragma once
#include <Engine/qState.h>

class qPlayerEffectState : public qState
{
public:
	CLONE(qPlayerEffectState);
	qPlayerEffectState();
	~qPlayerEffectState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

