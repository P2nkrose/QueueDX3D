#pragma once
#include <Engine/qState.h>

class qPlayerCrashState : public qState
{
public:
	CLONE(qPlayerCrashState);
	qPlayerCrashState();
	~qPlayerCrashState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	qGameObject*	CrashHitBox;
	Vec3			OGScale;
	Vec3			OGColScale;

	bool			soundflag;
};

