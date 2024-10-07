#include "pch.h"
#include "qPlayerIdleToRunState.h"

#include <Scripts/qPlayerScript.h>

qPlayerIdleToRunState::qPlayerIdleToRunState()
	: qState((UINT)STATE_TYPE::PLAYERIDLETORUNSTATE)
{
}

qPlayerIdleToRunState::~qPlayerIdleToRunState()
{
}

void qPlayerIdleToRunState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(3, 20, true);
}

void qPlayerIdleToRunState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
		{
			ChangeState(L"Run");
		}
		else
		{
			ChangeState(L"RunToIdle");
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



void qPlayerIdleToRunState::Exit()
{
}
