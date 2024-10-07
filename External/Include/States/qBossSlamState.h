#pragma once
#include <Engine/qState.h>

class qBossSlamState : public qState
{
public:
	CLONE(qBossSlamState);
	qBossSlamState();
	~qBossSlamState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

public:


private:
	qGameObject*		SlamHitbox;
	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;

	bool				HitboxFlag;

	bool				soundflag1;
	bool				soundflag2;
	bool				soundflag3;
	bool				soundflag4;
	bool				soundflag5;
};

