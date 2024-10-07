#include "pch.h"
#include "qPlayerIdleUTurnState.h"

#include <Scripts/qPlayerScript.h>

qPlayerIdleUTurnState::qPlayerIdleUTurnState()
	: qState((UINT)STATE_TYPE::PLAYERIDLEUTURNSTATE)
{
}

qPlayerIdleUTurnState::~qPlayerIdleUTurnState()
{
}

void qPlayerIdleUTurnState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(5, 25, true);
}

void qPlayerIdleUTurnState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
		{
			ChangeState(L"IdleToRun");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}

	if (KEY_TAP(KEY::S))
	{
		ChangeState(L"BookShoot");
	}

	if (KEY_TAP(KEY::D))
	{
		ChangeState(L"Crash");
	}

	if (KEY_TAP(KEY::F))
	{
		ChangeState(L"Range");
	}
}

void qPlayerIdleUTurnState::Exit()
{
}
