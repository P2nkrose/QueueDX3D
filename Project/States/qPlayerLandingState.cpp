#include "pch.h"
#include "qPlayerLandingState.h"

#include <Scripts/qPlayerScript.h>

qPlayerLandingState::qPlayerLandingState()
	: qState((UINT)STATE_TYPE::PLAYERLANDINGSTATE)
{
}

qPlayerLandingState::~qPlayerLandingState()
{
}

void qPlayerLandingState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(9, 15, false);

	//GetOwner()->RigidBody()->SetGround(true);
}

void qPlayerLandingState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}
}

void qPlayerLandingState::Exit()
{
	
}
