#pragma once
#include <Engine/qState.h>

class qPlayerTeleportFinishState : public qState
{
public:
	CLONE(qPlayerTeleportFinishState);
	qPlayerTeleportFinishState();
	~qPlayerTeleportFinishState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
};

