#pragma once
#include <Engine/qState.h>

class qPlayerBookShootState : public qState
{
public:
	CLONE(qPlayerBookShootState);
	qPlayerBookShootState();
	~qPlayerBookShootState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

