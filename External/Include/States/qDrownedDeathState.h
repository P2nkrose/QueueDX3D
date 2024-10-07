#pragma once
#include <Engine/qState.h>

class qDrownedDeathState : public qState
{
public:
	CLONE(qDrownedDeathState);
	qDrownedDeathState();
	~qDrownedDeathState();


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

