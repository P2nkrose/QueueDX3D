#pragma once
#include <Engine/qState.h>

class qGhostUturnState : public qState
{
public:
	CLONE(qGhostUturnState);
	qGhostUturnState();
	~qGhostUturnState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

