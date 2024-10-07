#pragma once
#include <Engine/qState.h>

class qPlayerGetItemState : public qState
{
public:
	CLONE(qPlayerGetItemState);
	qPlayerGetItemState();
	~qPlayerGetItemState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
};

