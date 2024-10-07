#pragma once
#include <Engine/qState.h>

class qDrownedUturnState : public qState
{
public:
	CLONE(qDrownedUturnState);
	qDrownedUturnState();
	~qDrownedUturnState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGScale;
	Vec3			OGColScale;
};

