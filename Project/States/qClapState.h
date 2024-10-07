#pragma once
#include <Engine/qState.h>

class qClapState : public qState
{
public:
	CLONE(qClapState);
	qClapState();
	~qClapState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

