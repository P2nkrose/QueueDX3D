#pragma once
#include <Engine/qState.h>

class qLoading1State : public qState
{
public:
	CLONE(qLoading1State);
	qLoading1State();
	~qLoading1State();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

