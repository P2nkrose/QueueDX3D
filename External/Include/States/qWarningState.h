#pragma once
#include <Engine/qState.h>

class qWarningState : public qState
{
public:
	CLONE(qWarningState);
	qWarningState();
	~qWarningState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

