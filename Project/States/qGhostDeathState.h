#pragma once
#include <Engine/qState.h>

class qGhostDeathState : public qState
{
public:
	CLONE(qGhostDeathState);
	qGhostDeathState();
	~qGhostDeathState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	Vec3			OGScale;
	Vec3			OGColScale;

	bool			Destroyflag;
	bool			Soulflag;

	bool			soundflag;
};

