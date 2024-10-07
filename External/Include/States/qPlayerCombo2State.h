#pragma once
#include <Engine/qState.h>

class qPlayerCombo2State : public qState
{
public:
	CLONE(qPlayerCombo2State);
	qPlayerCombo2State();
	~qPlayerCombo2State();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	qGameObject*	Combo2HitBox;
	Vec3			OGScale;
	Vec3			OGColScale;

};

