#pragma once
#include <Engine/qState.h>

class qGameObject;

class qGhostAttackState : public qState
{
public:
	CLONE(qGhostAttackState);
	qGhostAttackState();
	~qGhostAttackState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qGameObject*	GhostAttackHitbox;
};

