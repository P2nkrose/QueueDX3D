#pragma once
#include <Engine/qState.h>

class qPlayerKrushState : public qState
{
public:
	CLONE(qPlayerKrushState);
	qPlayerKrushState();
	~qPlayerKrushState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	qGameObject*	KrushHitBox;
	Vec3			OGScale;
	Vec3			OGColScale;

	float			m_KrushSpeed;

	bool			soundflag;
};

