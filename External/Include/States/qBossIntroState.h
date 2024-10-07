#pragma once
#include <Engine/qState.h>

class qBossIntroState : public qState
{
public:
	CLONE(qBossIntroState);
	qBossIntroState();
	~qBossIntroState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
};

