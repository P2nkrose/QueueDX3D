#pragma once
#include <Engine/qState.h>

class qBossDeathState : public qState
{
public:
	CLONE(qBossDeathState);
	qBossDeathState();
	~qBossDeathState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;

	bool				soundflag;
};

