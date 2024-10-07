#pragma once
#include <Engine/qState.h>

class qPlayerTeleportState : public qState
{
public:
	CLONE(qPlayerTeleportState);
	qPlayerTeleportState();
	~qPlayerTeleportState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGScale;
	Vec3			OGColScale;
};

