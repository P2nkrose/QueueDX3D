#include "pch.h"
#include "qPlayerRunToIdleState.h"

#include <Scripts/qPlayerScript.h>

qPlayerRunToIdleState::qPlayerRunToIdleState()
	: qState((UINT)STATE_TYPE::PLAYERRUNTOIDLESTATE)
{
}

qPlayerRunToIdleState::~qPlayerRunToIdleState()
{
}

void qPlayerRunToIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(4, 20, true);
}

void qPlayerRunToIdleState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
	
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"Run");
		}
	}

	// 애니메이션이 종료 되었다면
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

void qPlayerRunToIdleState::Exit()
{
}
