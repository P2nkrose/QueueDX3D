#include "pch.h"
#include "qPlayerFallingState.h"

#include <Scripts/qPlayerScript.h>

qPlayerFallingState::qPlayerFallingState()
	: qState((UINT)STATE_TYPE::PLAYERFALLINGSTATE)
{
}

qPlayerFallingState::~qPlayerFallingState()
{
}

void qPlayerFallingState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(8, 15, true);
}

void qPlayerFallingState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (GetOwner()->RigidBody()->IsGround())
	{
		ChangeState(L"Landing");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}

	if (KEY_PRESSED(KEY::DOWN) && KEY_TAP(KEY::G))
	{
		ChangeState(L"Krush");
	}



}

void qPlayerFallingState::Exit()
{
}
