#pragma once
#include <Engine/qState.h>

class qSkeletonDeathState : public qState
{
public:
	CLONE(qSkeletonDeathState);
	qSkeletonDeathState();
	~qSkeletonDeathState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
	Vec3			OGColOffset;

	bool			Destroyflag;
	bool			Soulflag;

	bool			soundflag;
};

