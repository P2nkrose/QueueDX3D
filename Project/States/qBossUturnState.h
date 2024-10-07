#pragma once
#include <Engine/qState.h>

class qBossUturnState : public qState
{
public:
	CLONE(qBossUturnState);
	qBossUturnState();
	~qBossUturnState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;
};

