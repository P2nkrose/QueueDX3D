#include "pch.h"
#include "qPlayerWaitState.h"

#include <Scripts/qPlayerScript.h>

qPlayerWaitState::qPlayerWaitState()
	: qState((UINT)STATE_TYPE::PLAYERWAITSTATE)
{
}

qPlayerWaitState::~qPlayerWaitState()
{
}

void qPlayerWaitState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void qPlayerWaitState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
		}
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
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

	if (KEY_TAP(KEY::V))
	{
		ChangeState(L"Hit");
	}


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerWaitState::Exit()
{
}
