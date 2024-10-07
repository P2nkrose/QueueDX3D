#pragma once
#include <Engine/qState.h>

class qGameObject;

class qBossPunchState : public qState
{
public:
	CLONE(qBossPunchState);
	qBossPunchState();
	~qBossPunchState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	qGameObject*		PunchHitbox;
	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;

	bool				HitboxFlag;

	bool				soundflag1;
	bool				soundflag2;
};

