#pragma once
#include <Engine/qState.h>

class qLogoState : public qState
{
public:
	CLONE(qLogoState);
	qLogoState();
	~qLogoState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

