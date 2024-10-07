#pragma once
#include <Engine/qState.h>

class qPlayerCombo4State : public qState
{
public:
	CLONE(qPlayerCombo4State);
	qPlayerCombo4State();
	~qPlayerCombo4State();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	qGameObject*	Combo4HitBox;
	Vec3			OGScale;
	Vec3			OGColScale;

};

