#pragma once
#include <Engine/qState.h>

class qBookEffectState : public qState
{
public:
	CLONE(qBookEffectState);
	qBookEffectState();
	~qBookEffectState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

