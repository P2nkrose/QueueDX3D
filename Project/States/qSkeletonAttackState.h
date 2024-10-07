#pragma once
#include <Engine/qState.h>

class qSkeletonAttackState : public qState
{
public:
	CLONE(qSkeletonAttackState);
	qSkeletonAttackState();
	~qSkeletonAttackState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	qGameObject*	SkeletonAttackHitBox;
	Vec3			OGPos;
	Vec3			OGScale;
	Vec3			OGColScale;
	Vec3			OGColOffset;

	bool			soundflag;
};

