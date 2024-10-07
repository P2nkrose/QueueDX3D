#pragma once
#include <Engine/qState.h>

class qBossBleedWaveState : public qState
{
public:
	CLONE(qBossBleedWaveState);
	qBossBleedWaveState();
	~qBossBleedWaveState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

