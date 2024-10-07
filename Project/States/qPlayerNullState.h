#pragma once
#include <Engine/qState.h>

class qPlayerNullState : public qState
{
public:
	CLONE(qPlayerNullState);
	qPlayerNullState();
	~qPlayerNullState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
};

